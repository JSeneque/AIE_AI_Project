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
void GridMap::CreateMap()
{
	// loop along the x axis, start from -1 to place either the ground tile or water tile
	for (int y = 0; y < m_rows; y++)
	{
		// loop along y axis, starting from -1 to place either the ground tile or water tile
		for (int x = 0; x < m_columns; x++)
		{
			// check if the current position is at the edge of the grid to store which tile
			if (x == 0 || x == m_columns - 1 || y == 0 || y == m_rows - 1)
			{
				// draw water tile
				m_grid.at(getGridIndex(x, y)) = Water;
			}
			else
			{
				// draw a ground tile
				m_grid.at(getGridIndex(x,y)) = Ground;
			}
		}
	}
}

void GridMap::Print()
{
	std::cout << "Map size: " << m_columns << " x " << m_rows << std::endl;
	std::cout << "Grid size: " << m_grid.size() << std::endl;
}

// returns the grid index from coordinates
int  GridMap::getGridIndex(int const column, int const row) const
{
	return row * m_columns + column;
}

int  GridMap::getScreenCoordinateX(int const index) const
{
	return (index % m_columns) * m_tileSize + m_tileSize / 2;
}

int  GridMap::getScreenCoordinateY(int const index) const
{
	return (index / m_columns) * m_tileSize + m_tileSize / 2;
}

void GridMap::setTileAt(int x, int y, ObjectType tileType)
{
	x /= m_tileSize;
	y /= m_tileSize;

	int index = x + m_columns * y;
	
	// check index is in range
	if ((x < m_columns && y < m_rows) && !(x == 0 || x == m_columns - 1 || y == 0 || y == m_rows - 1))
	{
		m_grid.at(x + m_columns * y) = tileType;
	}
	
}

int GridMap::getGridSize()
{
	return m_grid.size();
}

ObjectType GridMap::getGridMapTile(int index)
{
	return m_grid.at(index);
}

void GridMap::draw(aie::Renderer2D* renderer)
{
	drawTiles(renderer);
	//drawGridLine(renderer);
}

void GridMap::drawTiles(aie::Renderer2D* renderer)
{
	// draw map
	for (int i = 0; i < getGridSize(); ++i)
	{
		ObjectType objectType = getGridMapTile(i);

		// screen coordinates
		int x = getScreenCoordinateX(i);
		int y = getScreenCoordinateY(i);

		switch (objectType)
		{
		case Ground:
			// 107,142,35)
			renderer->setRenderColour(0.42, 0.56, .01, 1);
			break;
		case Water:
			renderer->setRenderColour(0.20, 0.80, 1.0, 1);
			break;
		}

		renderer->drawBox(x, y, m_tileSize, m_tileSize);
	}
}

void GridMap::drawHover(aie::Renderer2D* renderer, int mouseX, int mouseY)
{
	// maybe turn this into helper if I do this again
	int gridX = mouseX / m_tileSize;
	int gridY = mouseY / m_tileSize;

	int index = getGridIndex(gridX, gridY);

	int screenX = getScreenCoordinateX(index);
	int screenY = getScreenCoordinateY(index);

	// check index is in range
	if ((gridX < m_columns && gridY < m_rows) && !(gridX == 0 || gridX == m_columns - 1 || gridY == 0 || gridY == m_rows - 1))
	{
		renderer->setRenderColour(0.6, 0.8, .20, 1);
		renderer->drawBox(screenX, screenY, m_tileSize, m_tileSize);
	}
}

void GridMap::drawGridLine(aie::Renderer2D* renderer)
{

	renderer->setRenderColour(1, 1, 1, 1);
	// draw the vertical lines
	for (int i = 0; i <= m_columns; ++i)
	{
		renderer->drawLine(i * m_tileSize, 0, i * m_tileSize, m_columns * m_tileSize);
	}

	// draw the hortizontal lines
	for (int i = 0; i <= m_rows; ++i)
	{
		renderer->drawLine(0, i * m_tileSize, m_columns * m_tileSize, i * m_tileSize);
	}
}