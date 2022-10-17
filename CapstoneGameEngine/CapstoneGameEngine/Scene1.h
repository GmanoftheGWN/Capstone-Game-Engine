#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "AssetManager.h"

using namespace MATH;

/// Forward declarations 
union SDL_Event;

class Scene1 : public Scene {
private:
	std::unique_ptr<AssetManager> assetManager;
public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event& sdlEvent);
};


#endif // SCENE1_H
