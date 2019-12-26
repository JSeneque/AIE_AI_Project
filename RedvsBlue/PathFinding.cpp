#include "PathFinding.h"



PathFinding::PathFinding()
{
}


PathFinding::~PathFinding()
{
}

PathFinding::PathFinding(int width, int height)
{
	m_grid.clear();
	m_grid.resize(width * height);
}

std::list<const PathNode*> PathFinding::FindPath(PathNode* startNode, PathNode* endNode)
{
	// add the start node to the open list
	m_openList.push_back(startNode);
	return m_path;
}