#include "Actor.h"
Actor::Actor(Ref<Component> parent_):Component(parent_) {}
Actor::~Actor() {
	OnDestroy();
}

bool Actor::OnCreate() {
	if (isCreated) return isCreated;
	for (auto component : components) {
		if (component->OnCreate() == false) {
			isCreated = false;
			return isCreated;
		}
	}
	isCreated = true;
	return isCreated;
}

void Actor::OnDestroy() {
	RemoveAllComponents();
	isCreated = false;
}
void Actor::Update(const float deltaTime) {
	std::cout << "Hello from Update\n";
}
void Actor::Render()const {}

void Actor::RemoveAllComponents() {
	for (auto component : components) {
		component->OnDestroy();
	}
	components.clear();
}

void Actor::ListComponents() const {
	std::cout << typeid(*this).name() << " contains the following components:\n";
	for (auto component : components) {
		std::cout << typeid(*component).name() << std::endl;
	}
	std::cout << '\n';
}