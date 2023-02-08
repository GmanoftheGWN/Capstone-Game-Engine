#ifndef AI_TEST_H
#define AI_TEST_H
#include "Scene.h"
#include "AssetManager.h"
#include "Graph.h"
#include "Tile.h"
#include "Path.h"

using namespace MATH;

/// Forward declarations 
union SDL_Event;

class AI_Test : public Scene {
public:
	std::unique_ptr<AssetManager> assetManager;

	float planeX = 50.0f;
	float planeY = 40.0f;

	Graph* graph;
	vector<Node*> nodes;
	int safeNode;
	int playerLocationNode;
	int characterLocationNode;

	vector<vector <Tile* >> tiles;
	float tileWidth = 2.0;
	float tileHeight = 2.0f;

	void createTiles(int rows, int cols);
	void calculateConnectionWeights();

	std::shared_ptr<Actor> target;
	Path* path;


public:
	explicit AI_Test(SceneManager* game_);
	virtual ~AI_Test();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event& sdlEvent);

	int getNodeAtLocation(Ref<Actor> actor);

};


#endif // AI_TEST_H

