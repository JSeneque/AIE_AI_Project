#pragma once
/*
	The Grid Map class will take care of creating the grid map and methods relating to position of the grids
	as well as returns the screen coordinates
*/
#include <vector>
#include "Graph.h"

class GridMap
{
public:
	GridMap(int c, int r, int t) : m_columns{ c }, m_rows{ r }, m_tileSize{ t } {};
	~GridMap();
	void CreateMap(int columns, int rows);
	void Print();

private:
	int							m_columns;
	int							m_rows;
	int							m_tileSize;
	int							m_leftBorder;
	int							m_bottomBorder;
	std::vector<ObjectType>		m_grid;
	// combined the others lists into a weighted nodes
	std::vector<Node>			m_nodeList;
	Node*						m_startPoint;
	Node*						m_endPoint;

};

