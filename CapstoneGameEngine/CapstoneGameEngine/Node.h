#ifndef NODE_H
#define NODE_H

#include "MMath.h"
#include "Tile.h"

using namespace std;
using namespace MATH;

class Tile;

class Node
{
private:
	int label;
	Vec3 position;
	bool obstructed;
	Tile* tile;

public:
	Node(int label_, Vec3 position_ = Vec3())
	{
		label = label_;
		position = position_;
		obstructed = false;
		tile = NULL;
	}
	~Node() {}
	int getLabel() { return label; }
	Vec3 getPos() { return position; }
	void setTile(Tile* tile_) { tile = tile_; }
	Tile* getTile() { return tile; }
	void setObstructed(bool obstructed_);
	bool getObstructed() { return obstructed; }
};

#endif
