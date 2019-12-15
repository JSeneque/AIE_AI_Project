#pragma once
#include <list>
#include <glm/glm.hpp>

enum TileType {
	Ground = 0,
	Water
};

enum UnitType {
	NoUnit,
	BlueSoldier,
	RedSoldier
};

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
	glm::vec2 position;

	UnitType unit;
	TileType tile;

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

