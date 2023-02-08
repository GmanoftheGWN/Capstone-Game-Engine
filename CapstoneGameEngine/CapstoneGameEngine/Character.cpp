#include "Character.h"

bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;
	Actor::OnCreate();
	
	return true;
}

void Character::Update(float deltaTime)
{
	Ref<Actor> target = std::make_shared<Actor>(nullptr);
	Vec3 targetPosition;

	// create a new overall steering output
	KinematicSteeringOutput* steering;
	steering = new KinematicSteeringOutput();

	// calculate and set values in the overall steering output
	if (stateMachine)
	{
		stateMachine->update();
		switch (stateMachine->getCurrentStateName())
		{
		case STATE::SEARCH:
			pathToANode();
			steerToSeekTarget(steering);
			break;
		case STATE::PURSUE:
			if (decider)
			{
				DecisionTreeNode* action = decider->makeDecision();
				Action* a = dynamic_cast<Action*>(action);
				switch (a->getValue()) {
				case ACTION_SET::PURSUE:
					this->RemoveComponent<SteeringBehaviour>();
					this->AddComponent<KinematicArrive>(shared_from_this(), scene->game->getPlayer(), 0.5f);
					steerToSeekTarget(steering);
					break;
				case ACTION_SET::INTERCEPT:
					this->RemoveComponent<SteeringBehaviour>();
					targetPosition = 0.5f * (scene->game->getPlayer()->GetComponent<TransformComponent>()->GetPosition() - dynamic_cast<AI_Test*>(scene)->nodes[dynamic_cast<AI_Test*>(scene)->safeNode]->getPos());
					target->AddComponent<TransformComponent>(nullptr, targetPosition, Quaternion());
					this->AddComponent<KinematicArrive>(shared_from_this(), target, 0.5f);
					steerToSeekTarget(steering);
					break;
				case ACTION_SET::PATH_TO_LAST_LOCATION:
					this->RemoveComponent<SteeringBehaviour>();
					pathToANode(dynamic_cast<AI_Test*>(scene)->getNodeAtLocation(scene->game->getPlayer()));
					steerToSeekTarget(steering);
					break;
				}
			}
			break;
		case STATE::DO_NOTHING:
			break;
		}
	}
	else {
		if (decider)
		{
			DecisionTreeNode* action = decider->makeDecision();
			Action* a = dynamic_cast<Action*>(action);
			switch (a->getValue()) {
			case ACTION_SET::EVADE:
				this->RemoveComponent<SteeringBehaviour>();
				this->AddComponent<KinematicFlee>(shared_from_this(), scene->game->getPlayer());
				steerToSeekTarget(steering);
				break;
			case ACTION_SET::FLEE_TO_SAFETY:
				this->RemoveComponent<SteeringBehaviour>();
				targetPosition = dynamic_cast<AI_Test*>(scene)->nodes[dynamic_cast<AI_Test*>(scene)->safeNode]->getPos();
				target->AddComponent<TransformComponent>(nullptr, targetPosition, Quaternion());
				this->AddComponent<KinematicArrive>(shared_from_this(), target, 0.5f);
				steerToSeekTarget(steering);
				break;
			case ACTION_SET::DO_NOTHING:
				break;
			}
		}
	}
	
	// apply the steering to the equations of motion
	this->GetComponent<KinematicBody>()->Update(deltaTime, steering);

	// clean up memory
	// (delete only those objects created in this function)
	if (steering) {
		delete steering;
	}
}

void Character::steerToSeekTarget(KinematicSteeringOutput* steering) {
	vector<KinematicSteeringOutput*> steering_outputs;

	if(this->GetComponent<FollowAPath>()) { 
		steering_outputs.push_back(this->GetComponent<FollowAPath>()->getKinematicSteering()); 
	}
	if (this->GetComponent<KinematicArrive>()) {
		steering_outputs.push_back(this->GetComponent<KinematicArrive>()->getKinematicSteering());
	}
	if (this->GetComponent<KinematicFlee>()) {
		steering_outputs.push_back(this->GetComponent<KinematicFlee>()->getKinematicSteering());
	}

	for (unsigned i = 0; i < steering_outputs.size(); i++) {
		if (steering_outputs[i]) {
			*steering += *steering_outputs[i];
		}
	}
}

void Character::addStateMachine() {
	stateMachine = new StateMachine(this);

	State* searchForPlayer = new State(STATE::SEARCH);
	State* pursuePlayer = new State(STATE::PURSUE);

	Condition* ifInView = new ConditionInView(this);

	searchForPlayer->addTransition(
		new Transition(ifInView, pursuePlayer)
	);

	stateMachine->setInitialState(searchForPlayer);

}

void Character::addDecisionTree(DECISION_TREE decisionTreeType) {
	DecisionTreeNode* falseNode;
	DecisionTreeNode* trueNode;

	switch (decisionTreeType)
	{
	case DECISION_TREE::SEEKER:
		falseNode = new Action(ACTION_SET::PATH_TO_LAST_LOCATION);
		trueNode = new CloserToPlayerThanTargetDecision(this, new Action(ACTION_SET::PURSUE), new Action(ACTION_SET::INTERCEPT));

		decider = new PlayerInViewDecision(this, trueNode, falseNode);

		break;
	case DECISION_TREE::HIDER:
		falseNode = new Action(ACTION_SET::DO_NOTHING);
		trueNode = new CloserToPlayerThanTargetDecision(this, new Action(ACTION_SET::EVADE), new Action(ACTION_SET::FLEE_TO_SAFETY));

		decider = new PlayerInViewDecision(this, trueNode, falseNode);

		break;
	}
}

void Character::pathToANode() {
	if (this->GetComponent<FollowAPath>()) {
		int currentNode = this->GetComponent<FollowAPath>()->getPath()->CurrentNode;
		if (currentNode == this->GetComponent<FollowAPath>()->getPath()->nodes.size() - 1)
		{
			int startNode = this->GetComponent<FollowAPath>()->getPath()->nodes[currentNode]->getLabel();
			int goalNode = std::rand() % 499;
			while (dynamic_cast<AI_Test*>(scene)->nodes[goalNode]->getObstructed()) {
				goalNode = std::rand() % 499;
			}

			vector<Node*> pathNodes;
			map<int, int> nodeNumbers = dynamic_cast<AI_Test*>(scene)->graph->AStar(startNode, goalNode);
			for (int i = goalNode; i != startNode; i = nodeNumbers[i]) {
				pathNodes.push_back(dynamic_cast<AI_Test*>(scene)->nodes[i]);
			}
			std::reverse(pathNodes.begin(), pathNodes.end());
			dynamic_cast<AI_Test*>(scene)->path = new Path(pathNodes);

			FollowAPath* steering_algorithm;
			std::shared_ptr target = std::make_shared<Actor>(nullptr);
			target->AddComponent<TransformComponent>(nullptr, Vec3(), Quaternion());
			this->RemoveComponent<FollowAPath>();
			this->AddComponent<FollowAPath>(shared_from_this(), target, 1.0f, dynamic_cast<AI_Test*>(scene)->path);
		}
	}
	else {
		int startNode = dynamic_cast<AI_Test*>(scene)->getNodeAtLocation(shared_from_this());
		int goalNode = std::rand() % 499;
		while (dynamic_cast<AI_Test*>(scene)->nodes[goalNode]->getObstructed()) {
			goalNode = std::rand() % 499;
		}

		vector<Node*> pathNodes;
		map<int, int> nodeNumbers = dynamic_cast<AI_Test*>(scene)->graph->AStar(startNode, goalNode);
		for (int i = goalNode; i != startNode; i = nodeNumbers[i]) {
			pathNodes.push_back(dynamic_cast<AI_Test*>(scene)->nodes[i]);
		}
		std::reverse(pathNodes.begin(), pathNodes.end());
		dynamic_cast<AI_Test*>(scene)->path = new Path(pathNodes);

		FollowAPath* steering_algorithm;
		std::shared_ptr target = std::make_shared<Actor>(nullptr);
		target->AddComponent<TransformComponent>(nullptr, Vec3(), Quaternion());
		this->AddComponent<FollowAPath>(shared_from_this(), target, 1.0f, dynamic_cast<AI_Test*>(scene)->path);
	}
}

void Character::pathToANode(int node_) {
	vector<Node*> pathNodes;
	map<int, int> nodeNumbers = dynamic_cast<AI_Test*>(scene)->graph->AStar(dynamic_cast<AI_Test*>(scene)->characterLocationNode, node_);
	for (int i = node_; i != dynamic_cast<AI_Test*>(scene)->characterLocationNode; i = nodeNumbers[i]) {
		pathNodes.push_back(dynamic_cast<AI_Test*>(scene)->nodes[i]);
	}
	std::reverse(pathNodes.begin(), pathNodes.end());
	dynamic_cast<AI_Test*>(scene)->path = new Path(pathNodes);

	FollowAPath* steering_algorithm;
	std::shared_ptr target = std::make_shared<Actor>(nullptr);
	target->AddComponent<TransformComponent>(nullptr, Vec3(), Quaternion());
	this->AddComponent<FollowAPath>(shared_from_this(), target, 1.0f, dynamic_cast<AI_Test*>(scene)->path);
}

void Character::HandleEvents(const SDL_Event& event)
{
	// handle events here, if needed
}

void Character::render()
{
	
}