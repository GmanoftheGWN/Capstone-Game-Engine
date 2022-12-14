#include <glew.h>
#include <iostream>
#include <SDL.h>
#include <algorithm>
#include "Debug.h"
#include "AI_Test.h"
#include "MMath.h"
#include "QMath.h"
#include "Actor.h"
#include "CameraActor.h"
#include "LightActor.h"
#include "Character.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "ShaderComponent.h"
#include "MaterialComponent.h"
#include "StaticBody.h"
#include "KinematicArrive.h"
#include "FollowAPath.h"
#include "Debug.h"

AI_Test::AI_Test(SceneManager* game_) {
	Debug::Info("Created AI_Test: ", __FILE__, __LINE__);
	game = game_;
	graph = NULL;
	nodes = {};
}

AI_Test::~AI_Test() {
	Debug::Info("Deleted AI_Test: ", __FILE__, __LINE__);
	OnDestroy();
}

bool AI_Test::OnCreate() {
	Debug::Info("Loading assets AI_Test: ", __FILE__, __LINE__);

	assetManager = std::make_unique<AssetManager>(SceneManager::SCENE_NUMBER::AITEST);

	AddActor<CameraActor>("Camera", nullptr, assetManager->GetAsset<CameraActor>("Camera"));

	AddActor<LightActor>("Light", nullptr, assetManager->GetAsset<LightActor>("Light"));

	/*AddActor<Actor>("Mario", nullptr, assetManager->GetAsset<Actor>("Mario"));
	AddActor<Actor>("Hammer", GetActor<Actor>("Mario"), assetManager->GetAsset<Actor>("Hammer"));*/

	AddActor<Player>("Player", nullptr, game->getPlayer());
	GetActor<Player>("Player")->AddComponent<MeshComponent>(assetManager->GetAsset<MeshComponent>("MarioMesh"));
	GetActor<Player>("Player")->AddComponent<MaterialComponent>(assetManager->GetAsset<MaterialComponent>("MarioTexture"));
	GetActor<Player>("Player")->AddComponent<ShaderComponent>(assetManager->GetAsset<ShaderComponent>("TextureShader"));
	GetActor<Player>("Player")->OnCreate(); GetActor<Player>("Player")->GetComponent<TransformComponent>()->setMaxAcceleration(12.0f);

	AddActor<Character>("NPC", nullptr, std::make_shared<Character>());
	GetActor<Character>("NPC")->AddComponent<KinematicBody>(std::make_shared<KinematicBody>(nullptr, Vec3(0.0f, 0.0f, 0.0f), Quaternion(), 6.0f, 10.0f));
	GetActor<Character>("NPC")->AddComponent<MeshComponent>(assetManager->GetAsset<MeshComponent>("MarioMesh"));
	GetActor<Character>("NPC")->AddComponent<MaterialComponent>(assetManager->GetAsset<MaterialComponent>("MarioTexture"));
	GetActor<Character>("NPC")->AddComponent<ShaderComponent>(assetManager->GetAsset<ShaderComponent>("TextureShader"));
	GetActor<Character>("NPC")->OnCreate(this);

	// create a tile with a node
	int cols = ceil(planeX / tileWidth);
	int rows = ceil(planeY / tileHeight);
	// this createTiles is also going to populate nodes list
	createTiles(rows, cols);
	
	//create the graph, an empty graph
	graph = new Graph();
	if (!graph->OnCreate(nodes))
	{
		printf("graph OnCreate failed. \n");
		return false;
	}

	calculateConnectionWeights();
	
	int startNode = 370;
	int goalNode = 82;

	GetActor<Character>("NPC")->GetComponent<KinematicBody>()->SetTransform(Vec3(nodes[startNode]->getPos().x, nodes[startNode]->getPos().y, 1.25f), QMath::angleAxisRotation(90.0f, Vec3(1.0f, 0.0f, 0.0f)));
	GetActor<Player>("Player")->GetComponent<TransformComponent>()->SetTransform(Vec3(tiles[rows-1][cols-1]->getNode()->getPos().x, tiles[rows-1][cols-1]->getNode()->getPos().y, 1.25f), QMath::angleAxisRotation(90.0f, Vec3(1.0f, 0.0f, 0.0f)));

	vector<Node*> pathNodes;
	map<int, int> nodeNumbers = graph->AStar(startNode, goalNode);
	for (int i = goalNode; i != startNode; i = nodeNumbers[i]) {
		pathNodes.push_back(nodes[i]);
	}
	std::reverse(pathNodes.begin(), pathNodes.end());
	path = new Path(pathNodes);

	FollowAPath* steering_algorithm;
	std::shared_ptr target = std::make_shared<Actor>(nullptr);
	target->AddComponent<TransformComponent>(nullptr, Vec3(), Quaternion());
	GetActor<Character>("NPC")->AddComponent<FollowAPath>(GetActor<Actor>("NPC"), target, 1.0f, path);

	return true;
}

void AI_Test::createTiles(int rows, int cols)
{
	tiles.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		tiles[i].resize(cols);
	}

	Node* n;
	Tile* t;
	int i, j, label;
	i = 0;
	j = 0;
	label = 0;

	for (float y = (0.5f * tileHeight) - planeY / 2; y < planeY / 2; y += tileHeight)
	{
		//do stuff for a row, where y stays constant
		for (float x = (0.5f * tileWidth) - planeX / 2; x < planeX / 2; x += tileWidth)
		{
			n = new Node(label, Vec3(x, y, 0.0f));
			t = new Tile(n, tileWidth, tileHeight, this);
			t->AddComponent<TransformComponent>(nullptr, Vec3(x, y, 0.0f), Quaternion(), Vec3(0.15f,0.15f,0.15f));
			n->setTile(t);
			if (i % 2 == 1) {
				if (j % 2 == 0) {
					if (i != 0) {
						if (j != 0) {
							n->setObstructed(true);
						}
					}
				}
			}
			nodes.push_back(n);
			tiles[i][j] = t;
			tiles[i][j]->OnCreate();

			label++;
			j++;
		}
		j = 0;
		i++;
	}
}

void AI_Test::calculateConnectionWeights()
{
	int rows = tiles.size();
	int cols = tiles[0].size();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//                 i+1,j
			//   i,j-1           i,j        i,j+1
			//                 i-1,j

			int from = tiles[i][j]->getNode()->getLabel();

			//left is i, j-1
			if (j > 0)
			{
				int to = tiles[i][j - 1]->getNode()->getLabel();
				graph->addWeightConnection(from, to, tileWidth);
			}
			//right is i,j+1
			if (j < cols - 1)
			{
				int to = tiles[i][j + 1]->getNode()->getLabel();
				graph->addWeightConnection(from, to, tileWidth);
			}
			//above is i+1,j
			if (i < rows - 1)
			{
				int to = tiles[i + 1][j]->getNode()->getLabel();
				graph->addWeightConnection(from, to, tileHeight);
			}
			//below is i-1,j
			if (i > 0)
			{
				int to = tiles[i - 1][j]->getNode()->getLabel();
				graph->addWeightConnection(from, to, tileHeight);
			}

		}
	}
}

void AI_Test::OnDestroy() {
	Debug::Info("Deleting assets AI_Test: ", __FILE__, __LINE__);
	actorContainer.clear();
}

void AI_Test::HandleEvents(const SDL_Event& sdlEvent) {
	game->getPlayer()->HandleEvents(sdlEvent);

	/*Ref<CameraActor> camera = GetActor<CameraActor>("Camera");
	Ref<TransformComponent> cameraTransform = camera->GetComponent<TransformComponent>();
	
	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT) {
			cameraTransform->SetTransform(cameraTransform->GetPosition() + Vec3(-1.0f, 0.0f, 0.0f), cameraTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
			cameraTransform->SetTransform(cameraTransform->GetPosition() + Vec3(1.0f, 0.0f, 0.0f), cameraTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP) {
			cameraTransform->SetTransform(cameraTransform->GetPosition() + Vec3(0.0f, 0.0f, 1.0f), cameraTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN) {
			cameraTransform->SetTransform(cameraTransform->GetPosition() + Vec3(0.0f, 0.0f, -1.0f), cameraTransform->GetQuaternion());
		}
		camera->UpdateViewMatrix();
		break;
	case SDL_MOUSEMOTION:
		break;

	case SDL_MOUSEBUTTONDOWN:
		break;

	case SDL_MOUSEBUTTONUP:
		break;

	default:
		break;
	}*/
}

void AI_Test::Update(const float deltaTime) {

	// Calculate and apply any steering for npc's
	GetActor<Character>("NPC")->Update(deltaTime);

	// Update player
	game->getPlayer()->Update(deltaTime);

	//Example AI wandering
	if (GetActor<Character>("NPC")->GetComponent<FollowAPath>()) {
		int currentNode = GetActor<Character>("NPC")->GetComponent<FollowAPath>()->getPath()->CurrentNode;
		if (currentNode == GetActor<Character>("NPC")->GetComponent<FollowAPath>()->getPath()->nodes.size() - 1)
		{
			int startNode = GetActor<Character>("NPC")->GetComponent<FollowAPath>()->getPath()->nodes[currentNode]->getLabel();
			int goalNode = std::rand() % 499;
			while (nodes[goalNode]->getObstructed()) {
				goalNode = std::rand() % 499;
			}

			vector<Node*> pathNodes;
			map<int, int> nodeNumbers = graph->AStar(startNode, goalNode);
			for (int i = goalNode; i != startNode; i = nodeNumbers[i]) {
				pathNodes.push_back(nodes[i]);
			}
			std::reverse(pathNodes.begin(), pathNodes.end());
			path = new Path(pathNodes);

			FollowAPath* steering_algorithm;
			std::shared_ptr target = std::make_shared<Actor>(nullptr);
			target->AddComponent<TransformComponent>(nullptr, Vec3(), Quaternion());
			GetActor<Character>("NPC")->RemoveComponent<FollowAPath>();
			GetActor<Character>("NPC")->AddComponent<FollowAPath>(GetActor<Actor>("NPC"), target, 1.0f, path);
		}
	}

}

void AI_Test::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& actor : actorContainer) {
		if (actor.second->GetComponent<ShaderComponent>()) {
			glUseProgram(actor.second->GetComponent<ShaderComponent>()->GetProgram());
			glUniformMatrix4fv(actor.second->GetComponent<ShaderComponent>()->GetUniformID("modelMatrix"), 1, GL_FALSE, actor.second->GetComponent<TransformComponent>()->GetTransformMatrix());
			glBindTexture(GL_TEXTURE_2D, actor.second->GetComponent<MaterialComponent>()->getTextureID());
			actor.second->GetComponent<MeshComponent>()->Render(GL_TRIANGLES);
		}
	}

	int rows = tiles.size();
	int cols = tiles[0].size();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (tiles[i][j]->GetComponent<ShaderComponent>()) {
				glUseProgram(tiles[i][j]->GetComponent<ShaderComponent>()->GetProgram());
				glUniformMatrix4fv(tiles[i][j]->GetComponent<ShaderComponent>()->GetUniformID("modelMatrix"), 1, GL_FALSE, tiles[i][j]->GetComponent<TransformComponent>()->GetTransformMatrix());
				glBindTexture(GL_TEXTURE_2D, tiles[i][j]->GetComponent<MaterialComponent>()->getTextureID());
				tiles[i][j]->GetComponent<MeshComponent>()->Render(GL_TRIANGLES);
			}
		}
	}

	glBindBuffer(GL_UNIFORM_BUFFER, GetActor<CameraActor>("Camera")->GetMatricesID());
	glBindBuffer(GL_UNIFORM_BUFFER, GetActor<LightActor>("Light")->GetLightDataID());

	glUseProgram(0);
}