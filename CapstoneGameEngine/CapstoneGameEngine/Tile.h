#ifndef TILE_H
#define TILE_H

#include "MeshComponent.h"
#include "MaterialComponent.h"
#include "ShaderComponent.h"
#include "ShapeComponent.h"
#include "Box.h"

#include "Node.h"

#include "Scene.h"

class Node;

class Tile : public Actor
{
private:
	Node* node;
	float width;
	float height;
	Uint8 r, g, b, a;
	Scene* scene;

	void setRGBA(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_)
	{
		r = r_;
		g = g_;
		b = b_;
		a = a_;
	}

public:
	Tile(Node* node_, float width_, float height_, Scene* scene_);
	~Tile() {}
	void Render();
	Node* getNode() { return node; }
};

#endif
