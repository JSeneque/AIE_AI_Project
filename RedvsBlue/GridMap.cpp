#include "GridMap.h"
#include "Global.h"

#include <iostream>

//
//GridMap::GridMap()
//{
//}


GridMap::~GridMap()
{
}

// this creates a grid of size passed by the columns and rows
void GridMap::CreateMap()
{
	// loop along the x axis, start from -1 to place either the ground tile or water tile
	for (int x = 0; x < m_columns; x++)
	{
		// loop along y axis, starting from -1 to place either the ground tile or water tile
		for (int y = 0; y < m_rows; y++)
		{
			// check if the current position is at the edge of the grid to store which tile
			if (x == 0 || x == m_columns - 1 || y == 0 || y == m_rows - 1)
			{
				// draw water tile
				m_grid.at(x + m_columns * y) = Water;
			}
			else
			{
				// draw a ground tile
				m_grid.at(x + m_columns * y) = Ground;
			}
		}
	}
}

void GridMap::Print()
{
	std::cout << "Map size: " << m_columns << " x " << m_rows << std::endl;
	std::cout << "Grid size: " << m_grid.size() << std::endl;
}