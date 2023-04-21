#pragma once

#include "Scene.h"

using namespace MATH;

/// Forward declarations 
union SDL_Event;

class OOP_Test : public Scene {
private:

public:

	float time;

	explicit OOP_Test();
	virtual ~OOP_Test();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event& sdlEvent);
};


