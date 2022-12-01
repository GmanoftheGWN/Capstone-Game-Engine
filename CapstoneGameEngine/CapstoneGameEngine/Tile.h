#ifndef TILE_H
#define TILE_H

#include "MeshComponent.h"
#include "MaterialComponent.h"
#include "ShaderComponent.h"

#include "Node.h"

#include "Scene.h"

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
	Tile(Node* node_, float width_, float height_, Scene* scene_) : Actor(nullptr)
	{
		node = node_;
		width = width_;
		height = height_;
		r = 0;
		g = 255;
		b = 255;
		a = 255;
		scene = scene_;

		this->AddComponent<MeshComponent>(nullptr, "meshes/Plane.obj");
		this->AddComponent<MaterialComponent>(nullptr, "textures/redCheckerPiece.png");
		this->AddComponent<ShaderComponent>(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	}
	~Tile() {}
	void Render();
	Node* getNode() { return node; }
};

#endif
