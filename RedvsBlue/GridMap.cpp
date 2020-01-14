#include "GridMap.h"

#include <iostream>




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
				m_grid.at(getGridIndex(x * m_tileSize, y * m_tileSize)) = Water;
			}
			else
			{
				// draw a ground tile
				m_grid.at(getGridIndex(x * m_tileSize, y * m_tileSize)) = Ground;
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
//int  GridMap::getGridIndex(int const column, int const row) const
//{
//	return row * m_columns + column;
//}

int  GridMap::getGridIndex(int const mouseX, int const mouseY) const
{
	if (CheckBounds(mouseX,mouseY)) 
	{
		// get the column based on the x position
		int column = mouseX / m_tileSize;
		// get the row based on the yt position
		int row = mouseY / m_tileSize;

		//return column + m_columns * row;
		return row * m_columns + column;
	}
	return -1;
	
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
	//drawUnits(renderer);
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

//void GridMap::drawUnits(aie::Renderer2D* renderer)
//{
//	// draw map
//	for (int i = 0; i < m_units.size(); ++i)
//	{
//		int index = m_units[i].getPosition();
//		// screen coordinates
//		int x = getScreenCoordinateX(index);
//		int y = getScreenCoordinateY(index);
//
//		// set the unit colour
//		Faction faction = m_units[i].getFaction();
//
//		if (faction == BlueFaction)
//			renderer->setRenderColour(0.42, 0.56, 1.0, 1);
//		else if (faction == RedFaction)
//			renderer->setRenderColour(1.0, 0.56, 0.42, 1);
//		
//		// draw unit
//		renderer->drawCircle(x , y , m_tileSize / 4);
//	}
//}

void GridMap::drawHover(aie::Renderer2D* renderer, int mouseX, int mouseY)
{
	// maybe turn this into helper if I do this again
	int gridX = getColumn(mouseX);
	int gridY = getRow(mouseY);

	int index = getGridIndex(mouseX, mouseY);

	int screenX = getScreenCoordinateX(index);
	int screenY = getScreenCoordinateY(index);

	float lineThickness = 5.0f;

	// check index is in range
	if ((gridX < m_columns && gridY < m_rows) && !(gridX == 0 || gridX == m_columns - 1 || gridY == 0 || gridY == m_rows - 1))
	{
		renderer->setRenderColour(1, 1, 1, 1);

		// top left horizontal line
		renderer->drawLine(screenX - (m_tileSize / 2), screenY - (m_tileSize / 2) + m_tileSize, (screenX + (m_tileSize * 0.25)) - (m_tileSize / 2), screenY - (m_tileSize / 2) + m_tileSize, lineThickness);
		// top right horizontal line
		renderer->drawLine(screenX + (m_tileSize * 0.25), screenY - (m_tileSize / 2) + m_tileSize, screenX + (m_tileSize / 2), screenY - (m_tileSize / 2) + m_tileSize, lineThickness);

		// bottom left horizontal line
		renderer->drawLine(screenX - (m_tileSize / 2) , screenY - (m_tileSize /2 ), (screenX + (m_tileSize * 0.25)) - (m_tileSize / 2), screenY - (m_tileSize / 2), lineThickness);
		// bottom right horizontal line
		renderer->drawLine(screenX + (m_tileSize * 0.25), screenY - (m_tileSize / 2), screenX + (m_tileSize / 2), screenY - (m_tileSize / 2), lineThickness);

		// top left vertical line
		renderer->drawLine(screenX - (m_tileSize / 2), screenY - (m_tileSize / 2) + m_tileSize, screenX - (m_tileSize / 2), screenY - (m_tileSize / 2) + m_tileSize - (m_tileSize * 0.25), lineThickness);

		// top right vertical line
		renderer->drawLine(screenX + (m_tileSize * 0.5), screenY - (m_tileSize / 2) + m_tileSize, screenX + (m_tileSize / 2), screenY - (m_tileSize / 2) + m_tileSize - (m_tileSize * 0.25), lineThickness);
	
		// bottom left vertical line
		renderer->drawLine(screenX - (m_tileSize / 2), screenY - (m_tileSize / 2) , screenX - (m_tileSize / 2), screenY - (m_tileSize / 2)  + (m_tileSize * 0.25), lineThickness);

		// bottom right vertical line
		renderer->drawLine(screenX + (m_tileSize * 0.5), screenY - (m_tileSize / 2), screenX + (m_tileSize / 2), screenY - (m_tileSize / 2) + (m_tileSize * 0.25), lineThickness);
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

//void GridMap::addUnit(Unit unit)
//{
//	m_units.push_back(unit);
//}

int GridMap::getColumn(int mouseX) const
{
	return mouseX / m_tileSize;
}

int GridMap::getRow(int mouseY) const
{
	return mouseY / m_tileSize;
}

bool GridMap::CheckBounds(int const mouseX, int const mouseY) const
{
	return (m_columns > getColumn(mouseX) && (m_rows > getRow(mouseY)));
}

