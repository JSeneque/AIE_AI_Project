#include "Grid.h"
#include <iostream>


Grid::Grid()
{
}

// constructor for a specify size of grid
Grid::Grid(int width, int height) 
	: m_width  { width }
	, m_height { height }
{

}

// deallocates the memory and cleans up space
Grid::~Grid()
{
	// clean up dymanic array
	for (int i = 0; i < m_height; ++i) {
		delete[] gridArray[i];
	}
	delete[] gridArray;
}

// allocates the memory for the grid at runtime
void Grid::Initialise()
{
	for (int i = 0; i < m_height; ++i) {
		gridArray[i] = new int[m_width];
	}
}

// For debug purposes: prints out the grid to console
void Grid::Print()
{
	std::cout << "Grid size: " << m_width << " x " << m_height << std::endl;
	

}
