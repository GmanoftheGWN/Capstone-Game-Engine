#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include "Player.h"
class Player;

class SceneManager  {
public:
	Ref<Player> player;
	Ref<Player> getPlayer() { return player; }

	SceneManager();
	~SceneManager();
	void Run();
	bool Initialize(std::string name_, int width_, int height_);
	void HandleEvents();

	enum class SCENE_NUMBER {
		SCENE0 = 0,
		SCENE1,
		AITEST,
		SCENE3,
		SCENE4,
		SCENE5,
		SCENE6
	};
	
private:
	class Scene* currentScene;
	class Timer* timer;
	class Window* window;

	unsigned int fps;
	bool isRunning;
	bool fullScreen;
	void BuildNewScene(SCENE_NUMBER scene_);
};


#endif // SCENEMANAGER_H