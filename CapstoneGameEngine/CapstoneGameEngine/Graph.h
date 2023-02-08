#ifndef GRAPH_H
#define GRAPH_H

#include <vector> // from STL
#include <map>
#include <queue>
#include "Node.h"

using namespace std;

class Graph
{
private:
	// a list of the nodes
	// I could use STL vecotr, but map matches some textbooks
	map<int, Node*> node;

	// a 2D matrix of the connection costs
	vector< vector< float > > cost;

public:
	Graph();
	~Graph();
	bool OnCreate(vector< Node* > nodes_);
	int numNodes();
	Node* getNode(int label) { return node[label]; }
	void addWeightConnection(int fromNode, int toNode, float weight);
	vector<int> neighbours(int fromNode);
	map<int, int> AStar(int startNode, int goalNode);
	float Heurisitic(int a, int b);
};

#endif
