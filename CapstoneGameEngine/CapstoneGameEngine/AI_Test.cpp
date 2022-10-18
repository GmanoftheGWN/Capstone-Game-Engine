#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "AI_Test.h"
#include "MMath.h"
#include "QMath.h"
#include "Actor.h"
#include "CameraActor.h"
#include "LightActor.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "ShaderComponent.h"
#include "MaterialComponent.h"
#include "Debug.h"

AI_Test::AI_Test() {
	Debug::Info("Created AI_Test: ", __FILE__, __LINE__);
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

	AddActor<Actor>("Mario", nullptr, assetManager->GetAsset<Actor>("Mario"));

	AddActor<Actor>("Hammer", GetActor<Actor>("Mario"), assetManager->GetAsset<Actor>("Hammer"));

	return true;
}

void AI_Test::OnDestroy() {
	Debug::Info("Deleting assets AI_Test: ", __FILE__, __LINE__);
	actorContainer.clear();
}

void AI_Test::HandleEvents(const SDL_Event& sdlEvent) {
	Ref<CameraActor> camera = GetActor<CameraActor>("Camera");
	Ref<TransformComponent> cameraTransform = camera->GetComponent<TransformComponent>();
	Ref<Actor> mario = GetActor<Actor>("Mario");
	Ref<TransformComponent> marioTransform = mario->GetComponent<TransformComponent>();
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
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W) {
			marioTransform->SetTransform(marioTransform->GetPosition() + Vec3(0.0f, 0.0f, -1.0f), marioTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A) {
			marioTransform->SetTransform(marioTransform->GetPosition() + Vec3(-1.0f, 0.0f, 0.0f), marioTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S) {
			marioTransform->SetTransform(marioTransform->GetPosition() + Vec3(0.0f, 0.0f, 1.0f), marioTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			marioTransform->SetTransform(marioTransform->GetPosition() + Vec3(1.0f, 0.0f, 0.0f), marioTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_E) {
			marioTransform->SetTransform(marioTransform->GetPosition(), marioTransform->GetQuaternion() * QMath::angleAxisRotation(-2.0f, Vec3(0.0f, 1.0f, 0.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Q) {
			marioTransform->SetTransform(marioTransform->GetPosition(), marioTransform->GetQuaternion() * QMath::angleAxisRotation(2.0f, Vec3(0.0f, 1.0f, 0.0f)));
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
	}
}

void AI_Test::Update(const float deltaTime) {

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

	glBindBuffer(GL_UNIFORM_BUFFER, GetActor<CameraActor>("Camera")->GetMatricesID());
	glBindBuffer(GL_UNIFORM_BUFFER, GetActor<LightActor>("Light")->GetLightDataID());

	glUseProgram(0);
}