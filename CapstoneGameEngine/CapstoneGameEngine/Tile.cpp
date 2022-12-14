#include "Tile.h"

Tile::Tile(Node* node_, float width_, float height_, Scene* scene_) : Actor(nullptr)
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

	GEOMETRY::Box box;
	box.set(Vec3(0.0f, 0.0f, -4.0f), Vec3(1.0f, 1.0f, 1.0f), Quaternion());
	this->AddComponent<ShapeComponent>(nullptr, box);
}

void Tile::Render()
{
	

}