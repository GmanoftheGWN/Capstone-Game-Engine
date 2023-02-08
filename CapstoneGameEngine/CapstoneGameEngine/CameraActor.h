#pragma once
#include "Actor.h"
#include "Matrix.h"
#include <glew.h>

using namespace MATH;

class CameraActor :public Actor {
private:
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	GLuint uboMatricesID;
	const GLuint bindingPoint = 0;	//This must be unique to the camera = 0, lights = 1

public:
	CameraActor(Ref<Component> parent_);
	virtual ~CameraActor();

	bool OnCreate() override;
	void OnDestroy() override;
	Matrix4 GetProjectionMatrix() const { return projectionMatrix; }
	Matrix4 GetViewMatrix() const { return viewMatrix; }
	GLuint GetMatricesID() const { return uboMatricesID; }

	void UpdateProjectionMatrix(const float fovy, const float aspectRatio, const float near, const float far);
	void UpdateViewMatrix();
};

