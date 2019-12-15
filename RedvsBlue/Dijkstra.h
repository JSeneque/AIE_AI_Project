#pragma once
#include <unordered_set>
#include "Graph.h"
#include <vector>
#include <algorithm>


std::list<const Node*> DijkstraSearch(Node* startNode, Node* endNode) {
		
	// validate the passed nodes
	if (!startNode || !endNode) {
		throw std::runtime_error("Null nodes passed in!");
	}

	if (startNode == endNode) {
		return std::list<const Node*>();
	}

	// initialise the starting node
	startNode->runningCost = 0.0f;
	startNode->parent = nullptr;

	// create temporary lists for storing nodes that are visiting/visited
	std::vector<Node*> openList;
	std::unordered_set<const Node*> closedList;

	// add the start node to the open list
	openList.push_back(startNode);

	// process while the open list is not empty
	while (!openList.empty())
	{
		// sorting by
		auto sortNodes = [](const Node* a, const Node* b) {
			return a->runningCost < b->runningCost;
		};

		// sort open list by the node gScore (running cost)
		std::sort(openList.begin(), openList.end(), sortNodes);

		// let the current node be the first item in the open list
		Node* currentNode = openList.front();

		// if the current node is the end node then exit loop
		if (currentNode == endNode)
			break;

		// remove the current node from the open list
		openList.erase(openList.begin());

		// add current node to the closed list 
		closedList.insert(currentNode);

		// for all the connections in the current node out to the destination
		for (auto& edge : currentNode->outgoingEdges)
		{
			// check the destination is not in the closed list
			if (std::find(closedList.begin(), closedList.end(), edge.destination) == closedList.end()) 
			{
				// calculate the score and update its parent
				float runningCost = currentNode->runningCost + edge.weight;

				// check the destination is not in the open list
				if (std::find(openList.begin(), openList.end(), edge.destination) == openList.end()) 
				{
					edge.destination->runningCost = runningCost;
					edge.destination->parent = currentNode;
					openList.push_back(edge.destination);
				}
				else if ( runningCost < edge.destination->runningCost)
				{
					edge.destination->runningCost = runningCost;
					edge.destination->parent = currentNode;
				}

			}
		}
	}

	// create a path in reverse from the end node to the start node
	std::list<const Node*> path;
	Node* current_Node = endNode;

	if (!endNode->parent)
		return path;

	while (current_Node)
	{
		path.push_front(current_Node);
		current_Node = current_Node->parent;
	}

	return path;


}




