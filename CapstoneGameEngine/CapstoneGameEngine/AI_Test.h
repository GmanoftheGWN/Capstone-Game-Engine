#ifndef AI_TEST_H
#define AI_TEST_H
#include "Scene.h"
#include "AssetManager.h"

using namespace MATH;

/// Forward declarations 
union SDL_Event;

class AI_Test : public Scene {
private:
	std::unique_ptr<AssetManager> assetManager;
public:
	explicit AI_Test();
	virtual ~AI_Test();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event& sdlEvent);
};


#endif // AI_TEST_H

