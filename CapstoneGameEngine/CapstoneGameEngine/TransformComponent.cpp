#include <iostream>
#include "TransformComponent.h"
#include "QMath.h"
#include "MMath.h"
#include "Actor.h"

TransformComponent::TransformComponent(Ref<Component> parent_):Component(parent_) {
	scale = Vec3(1.0f, 1.0f, 1.0f);
	pos = Vec3(0.0f, 0.0f, 0.0f);
	orientation = Quaternion(1.0f, Vec3(0.0f, 0.0f, 0.0f));
}

TransformComponent::TransformComponent(Ref<Component> parent_, Vec3 pos_, Quaternion orientation_, Vec3 scale_) : Component(parent_),
pos(pos_), orientation(orientation_), scale(scale_) {
}

TransformComponent::~TransformComponent() {
	OnDestroy();
}

bool TransformComponent::OnCreate() {
	if (isCreated) return isCreated;
	isCreated = true;
	return isCreated;
}

void TransformComponent::OnDestroy() {
	isCreated = false;
}

void TransformComponent::Update(const float deltaTime) {
	std::cout << "Hello from Update\n";
}

void TransformComponent::Render()const {}

Matrix4 TransformComponent::GetTransformMatrix() const
{
	if (parent) {
		return dynamic_cast<Actor*>(parent.get())->GetComponent<TransformComponent>()->GetTransformMatrix() * MMath::translate(pos) * MMath::scale(scale) * QMath::toMatrix4(orientation);
	}
	return MMath::translate(pos) * MMath::scale(scale) * QMath::toMatrix4(orientation);
}
