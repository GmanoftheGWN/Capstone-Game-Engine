#include "Node.h"

void Node::setObstructed(bool obstructed_) {
	obstructed = obstructed_;
	if (obstructed) {
		tile->RemoveComponent<MaterialComponent>();
		tile->AddComponent<MaterialComponent>(nullptr, "textures/blackCheckerPiece.png");
	}
	else {
		tile->RemoveComponent<MaterialComponent>();
		tile->AddComponent<MaterialComponent>(nullptr, "textures/redCheckerPiece.png");
	}
}