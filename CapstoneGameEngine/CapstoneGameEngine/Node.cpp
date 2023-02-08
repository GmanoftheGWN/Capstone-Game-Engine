#include "Node.h"

void Node::setObstructed(bool obstructed_) {
	obstructed = obstructed_;
	if (obstructed) {
		tile->RemoveComponent<MaterialComponent>();
		tile->AddComponent<MaterialComponent>(nullptr, "textures/blackCheckerPiece.png");
		tile->GetComponent<MaterialComponent>()->OnCreate();
	}
	else {
		tile->RemoveComponent<MaterialComponent>();
		tile->AddComponent<MaterialComponent>(nullptr, "textures/redCheckerPiece.png");
		tile->GetComponent<MaterialComponent>()->OnCreate();
	}
}