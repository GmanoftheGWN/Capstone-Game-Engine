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
#include "ShapeComponent.h"
#include "StaticBody.h"
#include "KinematicArrive.h"
#include "FollowAPath.h"
#include "Action.h"
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
	GEOMETRY::Capsule capsule;
	capsule.set(0.5f, Vec3(0.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, -1.0f));
	GetActor<Actor>("Player")->AddComponent<ShapeComponent>(nullptr, capsule);
	GetActor<Player>("Player")->OnCreate(); 
	GetActor<Player>("Player")->GetComponent<TransformComponent>()->setMaxAcceleration(12.0f);

	AddActor<Character>("NPC", nullptr, std::make_shared<Character>());
	GetActor<Character>("NPC")->AddComponent<KinematicBody>(std::make_shared<KinematicBody>(nullptr, Vec3(0.0f, 0.0f, 0.0f), Quaternion(), 6.0f, 10.0f));
	GetActor<Character>("NPC")->AddComponent<MeshComponent>(assetManager->GetAsset<MeshComponent>("MarioMesh"));
	GetActor<Character>("NPC")->AddComponent<MaterialComponent>(assetManager->GetAsset<MaterialComponent>("MarioTexture"));
	GetActor<Character>("NPC")->AddComponent<ShaderComponent>(assetManager->GetAsset<ShaderComponent>("TextureShader"));
	GetActor<Character>("NPC")->addStateMachine();
	GetActor<Character>("NPC")->addDecisionTree(DECISION_TREE::SEEKER);
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
	
	int startNode = 400;
	int safeNode = 490;

	GetActor<Character>("NPC")->GetComponent<KinematicBody>()->SetTransform(Vec3(nodes[startNode]->getPos().x, nodes[startNode]->getPos().y, 1.25f), QMath::angleAxisRotation(90.0f, Vec3(1.0f, 0.0f, 0.0f)));
	GetActor<Player>("Player")->GetComponent<TransformComponent>()->SetTransform(Vec3(tiles[1][5]->getNode()->getPos().x, tiles[1][5]->getNode()->getPos().y, 1.25f), QMath::angleAxisRotation(90.0f, Vec3(1.0f, 0.0f, 0.0f)));

	AddActor<Actor>("Box1", nullptr, std::make_shared<Actor>(nullptr));
	GEOMETRY::Box box;
	box.set(Vec3(0.0f,0.0f,0.0f), Vec3(3.5f,3.5f,3.5f), Quaternion());
	GetActor<Actor>("Box1")->AddComponent<TransformComponent>(nullptr, Vec3(-14.75f, -15.75f, 0.0f), Quaternion());
	GetActor<Actor>("Box1")->AddComponent<ShapeComponent>(nullptr, box);
	GetActor<Actor>("Box1")->AddComponent<MeshComponent>(nullptr, "meshes/Cube.obj");
	GetActor<Actor>("Box1")->AddComponent<MaterialComponent>(nullptr, "textures/redCheckerPiece.png");
	GetActor<Actor>("Box1")->AddComponent<ShaderComponent>(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	GetActor<Actor>("Box1")->OnCreate();

	tiles[2][5]->getNode()->setObstructed(true);
	tiles[3][5]->getNode()->setObstructed(true);
	tiles[2][6]->getNode()->setObstructed(true);
	tiles[3][6]->getNode()->setObstructed(true);

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
			if (i % 2 == 0) {
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

int AI_Test::getNodeAtLocation(Ref<Actor> actor) {

	Tile* pickedActor = nullptr;

	Vec3 ray_worldStart = actor->GetComponent<TransformComponent>()->GetPosition();
	Vec3 ray_worldDirection = Vec3(0.0f,0.0f,-1.0f);

	MATH::Ray ray{ ray_worldStart, ray_worldDirection };

	// Loop through all the actors and check if the ray has collided with them
	// Pick the one with the smallest positive t value
	bool haveClickedOnSomething = false;
	GEOMETRY::RayIntersectionInfo rayInfo;
	for (auto it : nodes) {
		GEOMETRY::RayIntersectionInfo tempRayInfo;
		Tile* tile = it->getTile();
		Ref<TransformComponent> transformComponent = tile->GetComponent <TransformComponent>();
		Ref<ShapeComponent> shapeComponent = tile->GetComponent <ShapeComponent>();
		if (shapeComponent.get() == nullptr) { continue; }
		Vec3 position = Vec3(transformComponent->GetPosition().x, transformComponent->GetPosition().y, 0.0f);
		Matrix4 worldToObjectTransform = MMath::inverse(MMath::translate(position));
		Vec3 rayStartInObjectSpace = worldToObjectTransform * ray.start;
		Vec3 rayDirInObjectSpace = worldToObjectTransform.multiplyWithoutDividingOutW(Vec4(ray.dir, 0.0f));
		MATH::Ray rayInObjectSpace{ rayStartInObjectSpace, rayDirInObjectSpace };

		tempRayInfo = shapeComponent->shape->rayIntersectionInfo(rayInObjectSpace);
		if (tempRayInfo.isIntersected) {
			if (rayInfo.isIntersected == true && tempRayInfo.t > rayInfo.t) {
				continue;
			}
			rayInfo.isIntersected = true;
			rayInfo.t = tempRayInfo.t;
			rayInfo.intersectionPoint = tempRayInfo.intersectionPoint;
			Vec3 intersectionPoint = tile->GetComponent<TransformComponent>()->GetTransformMatrix() * rayInfo.intersectionPoint;
			pickedActor = tile;
		}
	}

	return pickedActor->getNode()->getLabel();
}

void AI_Test::OnDestroy() {
	Debug::Info("Deleting assets AI_Test: ", __FILE__, __LINE__);
	actorContainer.clear();
}

void AI_Test::HandleEvents(const SDL_Event& sdlEvent) {
	game->getPlayer()->HandleEvents(sdlEvent);

	Ref<CameraActor> camera = GetActor<CameraActor>("Camera");
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
		if (sdlEvent.button.button == SDL_BUTTON_RIGHT) {
			Vec3 mouseCoords(static_cast<float>(sdlEvent.button.x), static_cast<float>(sdlEvent.button.y), 1.0f);
			int viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);
			Matrix4 ndc = MMath::viewportNDC(viewport[2], viewport[3]);
			Matrix4 projection = camera->GetProjectionMatrix();
			Matrix4 view = camera->GetViewMatrix();
			Matrix4 rayTransform = MMath::inverse(ndc * projection);

			Vec3 ray_worldStart = { 0.0f,0.0f,0.0f };
			Vec3 ray_worldDirection = VMath::normalize(rayTransform * mouseCoords);

			MATH::Ray ray{ ray_worldStart, ray_worldDirection };

			// Loop through all the actors and check if the ray has collided with them
			// Pick the one with the smallest positive t value
			bool haveClickedOnSomething = false;
			GEOMETRY::RayIntersectionInfo rayInfo;
			std::string pickedActorName = "ThE VoId...";
			for (auto it : actorContainer) {
				GEOMETRY::RayIntersectionInfo tempRayInfo;
				Ref<Actor> actor = std::dynamic_pointer_cast<Actor>(it.second);
				Ref<TransformComponent> transformComponent = actor->GetComponent <TransformComponent>();
				Ref<ShapeComponent> shapeComponent = actor->GetComponent <ShapeComponent>();
				if (shapeComponent.get() == nullptr) { continue; }
				Matrix4 worldToObjectTransform = MMath::inverse(view * actor->GetComponent<TransformComponent>()->GetTransformMatrix());
				Vec3 rayStartInObjectSpace = worldToObjectTransform * ray.start;
				Vec3 rayDirInObjectSpace = worldToObjectTransform.multiplyWithoutDividingOutW(Vec4(ray.dir, 0.0f));
				MATH::Ray rayInObjectSpace{ rayStartInObjectSpace, rayDirInObjectSpace };

				tempRayInfo = shapeComponent->shape->rayIntersectionInfo(rayInObjectSpace);
				if (tempRayInfo.isIntersected) {
					if (rayInfo.isIntersected == true && tempRayInfo.t > rayInfo.t) {
						continue;
					}
					rayInfo.isIntersected = true;
					rayInfo.t = tempRayInfo.t;
					rayInfo.intersectionPoint = tempRayInfo.intersectionPoint;
					Vec3 intersectionPoint = actor->GetComponent<TransformComponent>()->GetTransformMatrix() * rayInfo.intersectionPoint;
					Ref<Actor> pickedActor = actor;
					pickedActorName = it.first;
					haveClickedOnSomething = true;
				}
			}
			std::cout << "You picked: " << pickedActorName << '\n';
		}
		break;

	case SDL_MOUSEBUTTONUP:
		break;

	default:
		break;
	}
}

void AI_Test::Update(const float deltaTime) {

	// Calculate and apply any steering for npc's
	GetActor<Character>("NPC")->Update(deltaTime);

	// Update player
	game->getPlayer()->Update(deltaTime);
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
			if (actor.second->GetComponent<ShapeComponent>()) {
				if (actor.second->GetComponent<ShapeComponent>()->shapeType == ShapeType::box) {
					actor.second->GetComponent<ShapeComponent>()->Render(GL_TRIANGLES);
				}
				else {
					actor.second->GetComponent<MeshComponent>()->Render(GL_TRIANGLES);
				}
			}
			else {
				actor.second->GetComponent<MeshComponent>()->Render(GL_TRIANGLES);
			}
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