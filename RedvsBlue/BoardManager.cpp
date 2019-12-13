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
	//gridPositions.resize(columns*rows);
}

void BoardManager::InitialiseList()
{
	m_grid.clear();
	m_grid.resize(m_columns * m_rows);
	m_hover.resize(m_columns * m_rows);

	for (int x = 1; x < m_columns - 1; x++)
	{
		for (int y = 1; y < m_rows - 1; y++)
		{
			m_grid.at(x*y) = Ground;
			m_hover.at(x*y) = false;
		}
	}
}

void BoardManager::BoardSetup()
{
	// set up outer wall and ground tiles
	//for (int x = 0; x < columns ; x++)
	//{
	//	for (int y = 0; y < rows  ; y++)
	//	{
	//		// if we are on the outer rim, draw water tile
	//		if (x == 0 || x == columns || y == 0 || y == rows)
	//		{
	//			// draw water tile
	//			grid.at(x*y) = 1;
	//		}
	//	}
	//}
}

void BoardManager::SetupScene(int level)
{
	InitialiseList();
	BoardSetup();
	
}

void BoardManager::Draw(aie::Renderer2D* renderer)
{
	// draw map
	for (int i = 0; i < m_grid.size(); ++i)
	{
		TileType tile = m_grid.at(i);

		// screen coordinates
		int x = (i % m_columns) * m_tileSize + m_tileSize / 2;
		int y = (i / m_columns) * m_tileSize + m_tileSize / 2;

		switch (tile)
		{
		case Ground:
			renderer->setRenderColour(0, 0.8, 0.3, 1);
			break;
		}

		if (m_hover.at(i))
		{
			renderer->setRenderColour(1, 0, 0, 1);
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
	 
	// check index is in range
	if (x < m_columns && y < m_rows)
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