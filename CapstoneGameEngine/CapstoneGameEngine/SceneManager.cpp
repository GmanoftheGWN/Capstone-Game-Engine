#include <SDL.h>
#include "SceneManager.h"
#include "Timer.h"
#include "Window.h"
#include "Scene0.h"
#include "Scene1.h"
#include "AI_Test.h"
#include "EnTT_Test.h"
#include "OOP_Test.h"

SceneManager::SceneManager(): 
	currentScene(nullptr), window(nullptr), timer(nullptr),
	fps(60), isRunning(false), fullScreen(false), player(nullptr) {
	Debug::Info("Starting the SceneManager", __FILE__, __LINE__);
}

SceneManager::~SceneManager() {
	if (currentScene) {
		delete currentScene;
		currentScene = nullptr;
	}
	
	if (timer) {
		delete timer;
		timer = nullptr;
	}

	if (window) {
		delete window;
		window = nullptr;
	}
	Debug::Info("Deleting the SceneManager", __FILE__, __LINE__);
}

bool SceneManager::Initialize(std::string name_, int width_, int height_) {

	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Failed to initialize Window object", __FILE__, __LINE__);
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		Debug::FatalError("Failed to initialize Timer object", __FILE__, __LINE__);
		return false;
	}

	// create player
	Ref<Component> parent;
	float mass = 1.0f;
	float radius = 0.5f;
	Quaternion orientation;
	float rotation = 0.0f;
	float angular = 0.0f;
	// These are not very good defaults, but they will prevent compiler warnings.
	float maxSpeed = 5.0f;
	float maxAcceleration = 10.0f;
	float maxRotation = 1.0f;
	float maxAngular = 1.0f;
	Vec3 pos(0.0f, 0.0f, 10.0f);
	Vec3 vel(0.0f, 0.0f, 0.0f);
	Vec3 accel(0.0f, 0.0f, 0.0f);

	player = std::make_shared<Player>
		(
			parent,
			pos,
			orientation,
			vel,
			accel,
			mass,
			radius,
			rotation,
			angular,
			maxSpeed,
			maxAcceleration,
			maxRotation,
			maxAngular,
			this
			);
	if (player->OnCreate() == false) {
		return false;
	}

	/********************************   Default first scene   ***********************/
	BuildNewScene(SCENE_NUMBER::ENTT_TEST);
	//BuildNewScene(SCENE_NUMBER::OOP_TEST);

	return true;
}

/// This is the whole game
void SceneManager::Run() {
	timer->Start();
	isRunning = true;
	while (isRunning) {
		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		HandleEvents();
		SDL_GL_SwapWindow(window->getWindow());
		SDL_Delay(timer->GetSleepTime(fps));
	}
}

void SceneManager::HandleEvents() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		const Uint8* state = SDL_GetKeyboardState(nullptr);
		if (sdlEvent.type == SDL_EventType::SDL_QUIT) {
			isRunning = false;
			return;
		}
		else if (sdlEvent.type == SDL_KEYDOWN) {
			switch (sdlEvent.key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE:
				isRunning = false;
				return;
				[[fallthrough]]; /// C17 Prevents switch/case fallthrough warnings
			case SDL_SCANCODE_F1:
				if (state[SDL_SCANCODE_RSHIFT] || state[SDL_SCANCODE_LSHIFT]) {
					//BuildNewScene(SCENE1_ADV);
				}
				else {
					BuildNewScene(SCENE_NUMBER::SCENE0);
				}
				break;
			case SDL_SCANCODE_F2:
				if (state[SDL_SCANCODE_RSHIFT] || state[SDL_SCANCODE_LSHIFT]) {
					/*BuildNewScene(SCENE1_ADV);*/
				}
				else {
					BuildNewScene(SCENE_NUMBER::SCENE1);
				}
				break;
			default:
				break;
			}
		}
		if (currentScene == nullptr) {
			Debug::FatalError("Failed to initialize Scene", __FILE__, __LINE__);
			isRunning = false;
			return;
		}
		currentScene->HandleEvents(sdlEvent);
	}
}

void SceneManager::BuildNewScene(SCENE_NUMBER scene) {
	bool status; 

	if (currentScene != nullptr) {
		delete currentScene;
		currentScene = nullptr;
	}

	switch (scene) {
	case SCENE_NUMBER::SCENE0:
		currentScene = new Scene0();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE1:
		currentScene = new Scene1();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::AITEST:
		currentScene = new AI_Test(this);
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::ENTT_TEST:
		currentScene = new EnTT_Test();
		status = currentScene->OnCreate();
		break;

	/*case SCENE_NUMBER::OOP_TEST:
		currentScene = new OOP_Test();
		status = currentScene->OnCreate();
		break;*/

	default:
		Debug::Error("Incorrect scene number assigned in the manager", __FILE__, __LINE__);
		currentScene = nullptr;
		break;
	}	
}


