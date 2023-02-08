#include <glew.h>
#include "LightActor.h"
#include "UBO_Padding.h"

LightActor::LightActor(Ref<Component> parent_, LightStyle LightStyle_, Vec3 location_, Vec4 colour_, float intensity_, Vec3 falloff_) :Actor(parent_),
lightStyle(LightStyle_), pos(location_), colour(colour_), intensity(intensity_), falloff(falloff_) {
}

LightActor::~LightActor() {
	OnDestroy();
}

bool LightActor::OnCreate()
{
	if (isCreated) return isCreated;

	size_t buffer_size = UBO_PADDING::VEC3 + UBO_PADDING::VEC4;

	glGenBuffers(1, &uboLightDataID);
	glBindBuffer(GL_UNIFORM_BUFFER, uboLightDataID);
	glBufferData(GL_UNIFORM_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);	//allocated memory
	size_t offset = 0;
	glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(Vec3), pos);
	offset = UBO_PADDING::VEC3;
	glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(Vec4), colour);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, uboLightDataID);

	isCreated = true;
	return isCreated;
}

void LightActor::OnDestroy()
{
	glDeleteBuffers(1, &uboLightDataID);
	isCreated = false;
}



