#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "AI_Test.h"
#include "TransformComponent.h"
#include "KinematicBody.h"
#include "SteeringBehaviour.h"
#include "Seek.h"
#include "Pursue.h"
#include "KinematicFlee.h"
#include "Evade.h"
#include "CollisionAvoidance.h"
#include "KinematicArrive.h"
#include "FollowAPath.h"

#include "Decision.h"		//which includes DecisionTreeNode.h
#include "CloserToPlayerThanTargetDecision.h"
#include "PlayerInViewDecision.h"
#include "Action.h"

class DecisionTreeNode;

#include "StateMachine.h"

using namespace std;

class Character : public Actor , public std::enable_shared_from_this<Character>
{
private:
	class Scene* scene;

    DecisionTreeNode* decider;
    class StateMachine* stateMachine;

public:
    Character(): Actor(nullptr) {
        scene = nullptr;
        decider = nullptr;
        stateMachine = nullptr;
    }

	~Character()
	{
		
	};
	bool OnCreate(Scene* scene_);
	void OnDestroy() {};

	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void render();
    void steerToSeekTarget(KinematicSteeringOutput* steering);

	void pathToANode();
	void pathToANode(int node_);

	void addStateMachine();
	void addDecisionTree(DECISION_TREE decisionTreeType);

	Scene* getScene() { return scene; }

};

#endif