#ifndef PATH_H
#define PATH_H

#include "Node.h"
#include <vector>

class Path {
public:
	vector<Node*> nodes;
	int CurrentNode;

	Path(vector<Node*> nodes_) {
		nodes = nodes_;
		CurrentNode = 0;
	}
	void incrementCurrentNode();
	Vec3 getCurrentNodePosition();
};

#endif //Path.h