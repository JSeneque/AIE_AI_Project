#include "BoardManager.h"
#include <iostream>




BoardManager::BoardManager()
{

}


BoardManager::~BoardManager()
{
}

void BoardManager::Print()
{
	std::cout << "Board size: " << m_columns << " x " << m_rows << std::endl;
	std::cout << "Grid size: " << m_grid.size() << std::endl;
}

void BoardManager::Start()
{
	// so if 5,9 mens  a minimum of 5 items and a maximum of 9
	m_waterTileCount = new Count(5, 9);
}

void BoardManager::InitialiseList()
{
	m_grid.clear();
	m_mapData.clear();

	m_grid.resize(m_columns * m_rows);
	m_hover.resize(m_columns * m_rows);
	m_mapData.resize(m_columns * m_rows);

	// set up outer water tiles
	for (int x = 0; x < m_columns ; x++)
	{
		for (int y = 0; y < m_rows ; y++)
		{
			// if we are on the outer rim, draw water tile
			if (x == 0 || x == m_columns - 1 || y == 0 || y == m_rows - 1)
			{
				// draw water tile
				m_grid.at(x + m_columns * y) = Water;
				m_mapData.at(x + m_columns * y) = 1;
			}
			else
			{
				m_grid.at(x + m_columns * y) = Ground;
				m_mapData.at(x + m_columns * y) = 0;

			}
			m_hover.at(x + m_columns * y) = false;
		}
	}

}

void BoardManager::SetupScene(int level)
{
	InitialiseList();	
	PlaceBlueTeam();
}

void BoardManager::Draw(aie::Renderer2D* renderer)
{
	// draw map
	for (int i = 0; i < m_grid.size(); ++i)
	{
		Object tile = m_grid.at(i);

		// screen coordinates
		int x = (i % m_columns) * m_tileSize + m_tileSize / 2;
		int y = (i / m_columns) * m_tileSize + m_tileSize / 2;

		switch (tile)
		{
		case Ground:
			// 107,142,35)
			renderer->setRenderColour(0.42, 0.56, .01, 1);
			break;
		case Water:
			// 107,142,35)
			renderer->setRenderColour(0.20, 0.80, 1.0, 1);
			break;
		case BlueSoldier:
			// 107,142,35)
			renderer->setRenderColour(0, 0, 0.56, 1);
			break;
		case RedSoldier:
			// 107,142,35)
			renderer->setRenderColour(1.0, 0, 0.0, 1);
			break;
		}


		if (m_hover.at(i))
		{
			// 154,205,50
			renderer->setRenderColour(0.6, 0.8, .20, 1);
		}

		renderer->drawBox(x, y, m_tileSize, m_tileSize);
	}

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

void BoardManager::Update(aie::Input* input)
{
	// get the mouse position
	int x = input->getMouseX() / m_tileSize;
	int y = input->getMouseY() / m_tileSize;
	// calculate the index
	int index = x + y * m_columns;

	ClearHoverList();
	 
	// check index is in range and is not on a water tile
	if ((x < m_columns && y < m_rows) && !(x == 0 || x == m_columns - 1 || y == 0 || y == m_rows - 1))
	{
		m_hover.at(index) = true;
	}
}

void BoardManager::ClearHoverList()
{
	for (auto& i : m_hover)
	{
		i = false;
	}
}

void BoardManager::PlaceBlueTeam()
{
	m_grid.at(41) = BlueSoldier;
	m_grid.at(58) = RedSoldier;
}