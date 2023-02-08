#pragma once
#include "Actor.h"
#include "Vector.h"

using namespace MATH;

enum class LightStyle {
	DirectionalLight = 1,
	PointLight,
	SkyLight,
	SpotLight
};

class LightActor : public Actor {
	LightActor(const LightActor&) = delete;
	LightActor(Actor&&) = delete;
	LightActor& operator=(const LightActor&) = delete;
	LightActor& operator=(LightActor&&) = delete;

private:
	LightStyle lightStyle;
	Vec3 pos;
	Vec4 colour;
	float intensity;
	Vec3 falloff;
	GLuint uboLightDataID;
	const GLuint bindingPoint = 1;

public:
	LightActor(Ref<Component> parent_, LightStyle LightStyle_, Vec3 location_, Vec4 colour_, float intensity_ = 1.0f, Vec3 faloff = Vec3(0.0f,0.0f,0.0f));
	~LightActor();
	bool OnCreate() override;
	void OnDestroy() override;
	Vec3 GetLightPos() const { return pos; }
	void SetLightPos(Vec3 pos_) { pos = pos_; }
	GLuint GetLightDataID() const { return uboLightDataID; }


};

