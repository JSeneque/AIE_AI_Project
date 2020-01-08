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
	GridMap(int c, int r, int t) : m_columns{ c }, m_rows{ r }, m_tileSize{ t }
	{
		m_grid.resize(m_columns * m_rows); 
	};

	~GridMap();
	void CreateMap();
	void Print();

private:
	int							m_columns;
	int							m_rows;
	int							m_tileSize;
	std::vector<ObjectType>		m_grid;


};

