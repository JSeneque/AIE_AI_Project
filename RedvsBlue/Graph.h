#pragma once
#include <list>
#include <glm/glm.hpp>
#include "Unit.h"
#include "Global.h"


struct Edge {
	// the node the edge is going to
	struct Node* destination = nullptr;
	// cost to travel to along
	float weight = std::numeric_limits<float>::max();

};
#include <limits>


struct Node {
	// id
	unsigned int id = ' ';
	// pathfinding
	float runningCost = 0.0f;
	// might replace the runningCost with gScore
	int gScore = 1;
	glm::vec2 position;

	//UnitType unit;
	Unit unit;

	Node* parent = nullptr;

	// graph structure
	std::list<Edge> outgoingEdges;
};


class Graph
{
public:
	Graph();
	~Graph();
};

