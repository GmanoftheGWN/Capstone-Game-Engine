#include "Path.h"

void Path::incrementCurrentNode()
{
	if (CurrentNode < nodes.size() - 1) {
		CurrentNode++;
	}
}

Vec3 Path::getCurrentNodePosition()
{
	return nodes[CurrentNode]->getPos();
}
