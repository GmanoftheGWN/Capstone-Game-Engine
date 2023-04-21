#pragma once

#include "Scene.h"
#include "External/EnTT/entt.hpp"

using namespace MATH;

/// Forward declarations 
union SDL_Event;

class EnTT_Test : public Scene {
private:
	entt::registry registry;

public:

	float time;

	explicit EnTT_Test();
	virtual ~EnTT_Test();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event& sdlEvent);
};
