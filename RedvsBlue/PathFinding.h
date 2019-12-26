#pragma once
#include <vector>
#include <list>

class PathNode {
public:
	PathNode(std::vector<PathNode> grid, int x, int y) : m_grid{ grid }, m_x{ x }, m_y{ y }{};

private:
	std::vector<PathNode>		m_grid;
	int m_x;
	int m_y;
	int m_gCost;
	int m_hCost;
	int m_fCost;
};


class PathFinding
{
public:
	PathFinding();
	PathFinding(int width, int height);
	~PathFinding();

//private:
	std::list<const PathNode*> FindPath(PathNode* startNode, PathNode* endNode);

	
private:
	std::vector<PathNode>			m_grid;
	std::list<const PathNode*>		m_path;
	std::list<PathNode*>			m_openList;
	std::list<PathNode*>			m_closedList;
	
};

