#include "GridMap.h"
#include <iostream>

//
//GridMap::GridMap()
//{
//}


GridMap::~GridMap()
{
}

// this creates a grid of size passed by the columns and rows
void GridMap::CreateMap(int columns, int rows)
{
	
}

void GridMap::Print()
{
	std::cout << "Map size: " << m_columns << " x " << m_rows << std::endl;
	std::cout << "Grid size: " << m_grid.size() << std::endl;
}