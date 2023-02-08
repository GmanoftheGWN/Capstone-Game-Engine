#include "Graph.h"

using namespace std;

Graph::Graph()
{

}


bool Graph::OnCreate(vector<Node*> nodes_)
{
	// ASSUMPTION: nodes_ vector has the node with label "i" in the "i" position of the vector

	// given a list of nodes
	// initialize a matrix of costs
	// with 0.0 weights
	int numNodes = nodes_.size();
	cost.resize(numNodes);

	for (int i = 0; i < numNodes; i++)
	{
		// add the nodes to internal list
		if ( i != nodes_[i]->getLabel() )
		{
			printf("node with label 'i' not in the 'i' position of the vector\n");
			return false;
		}
		node[i] = nodes_[i];

		//set up the connections
		cost[i].resize(numNodes);
		for (int j = 0; j < numNodes; j++)
		{
			//initialize connections
			cost[i][j] = 0.0f;
		}
	}

	return true;
}

Graph::~Graph()
{}

int Graph::numNodes()
{
	return node.size();
	// return cost.size();
}

void Graph::addWeightConnection(
	int fromNode, int toNode, float weight
)
{
	cost[fromNode][toNode] = weight;
}

vector<int> Graph::neighbours(int fromNode)
{
	vector<int> result = {};
	for (int j = 0; j < numNodes(); j++)
	{
		if (!node[j]->getObstructed()) {
			if (cost[fromNode][j] > 0.0f)
			{
				result.push_back(j);
			}
		}
	}
	return result;
}

// From https://github.com/ProfessorGailHarris/PriorityQueueUsingSTL
struct NodeAndPriority {
	int node;
	float priority;
	int getNode() { return node; }
	NodeAndPriority(int node_, float priority_)
	{
		node = node_;
		priority = priority_;
	}
};

struct ComparePriority
{
	bool operator()(NodeAndPriority const& lhs, NodeAndPriority const& rhs)
	{
		// make it a min queue
		return lhs.priority > rhs.priority;
	}
};

map<int, int> Graph::AStar(
	int startNode, int goalNode
)
{
	// declare helper variables
	float new_cost;
	int		current;

	// declare current NodeAndPriority
	NodeAndPriority* currentNodeAndPriority;
	currentNodeAndPriority = new NodeAndPriority(startNode, 0.0f);

	// set up priority queue for frontier of nodes
	priority_queue< NodeAndPriority, deque<NodeAndPriority>, ComparePriority > frontier;
	frontier.push(*currentNodeAndPriority);

	// track solution path
	map<int, int> came_from;

	// store cost so far to reach a node
	map<int, float> cost_so_far;
	cost_so_far[startNode] = 0.0;

	// TODO implement the algorithm
	
	// start looping through the frontier
	while (!frontier.empty())
	{
		// get the node from the top of the frontier, put it in "current"
		current = frontier.top().node;
		// pop it off 
		frontier.pop();
		// if its the goal, then break out of the loop
		if (current == goalNode) {
			break;
		}
		// for the neighbours of current node
		vector<int> nodeNeighbours = neighbours(current);
		//for (int i = 0; i < nodeNeighbours.size(); i++)
		for(int next : neighbours(current))
		{
			// calculate new_cost
			new_cost = cost_so_far[current] + cost[current][next];
			// if neighbour is not in cost_so_far OR new_cost is lower
			if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
			{
				// found a better path so update structure (look at pseudocode algorithm)
				cost_so_far[next] = new_cost;
				frontier.push(*new NodeAndPriority(next, new_cost + Heurisitic(goalNode, next)));
				came_from[next] = current;
			}
		}

	}
	return came_from;
}

float Graph::Heurisitic(int a, int b) {
	//Manhattan distance on a square grid
	return abs(node[a]->getPos().x - node[b]->getPos().x) + abs(node[a]->getPos().y - node[b]->getPos().y);
}
