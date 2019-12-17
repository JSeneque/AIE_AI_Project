#include "BoardManager.h"
#include <iostream>
#include "Dijkstra.h"

std::list<const Node*> DijkstraSearch(Node* startNode, Node* endNode);

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
	BuildNodeList();

	m_startPoint = &m_nodeList[41];
	m_endPoint = &m_nodeList[58];

	m_path = DijkstraSearch(m_startPoint, m_endPoint);
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

	// set the path colour
	renderer->setRenderColour(1, 0.5, 0.3, 1);

	// check the path is not empty
	if (m_path.size() > 2)
	{
		// setup for loop with two initialisers
		for (auto i = m_path.begin(), j = std::next(m_path.begin()); j != m_path.end(); ++i, ++j)
		{
			// get the starting and ending points
			unsigned int id = (*i)->id;
			unsigned int jd = (*j)->id;
			float ix = (id % m_columns) * m_tileSize + m_tileSize / 2;
			float iy = (id / m_columns) * m_tileSize + m_tileSize / 2;
			float jx = (jd % m_columns) * m_tileSize + m_tileSize / 2;
			float jy = (jd / m_columns) * m_tileSize + m_tileSize / 2;

			// draw line
			renderer->drawLine(ix, iy, jx, jy, 4);

		}
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
	m_mapData.at(41) = 1;
	m_grid.at(58) = RedSoldier;
	m_mapData.at(58) = 1;
}

void BoardManager::BuildNodeList()
{
	// clear the node list
	m_nodeList.clear();
	// set the size of the list
	m_nodeList.resize(m_columns * m_rows);
	
	// initialise each node
	for (int i = 0; i < m_nodeList.size(); ++i)
	{
		// set id
		m_nodeList[i].id = i;
		// a lambda function to calculate weight and create edges
		auto assignWeight = [&](int id)
		{
			float weight = m_grid[id] == Water || m_grid[id] == BlueSoldier || m_grid[id] == RedSoldier ? 1000000.0f : 1.0f;
			m_nodeList[i].outgoingEdges.push_back(Edge{ &m_nodeList[id], weight });

		};

		// check left of tile
		if ( i % m_columns != 0)
		{
			assignWeight(i - 1);
		}

		// check right of tile
		if ((i + 1) % m_columns != 0)
		{
			assignWeight(i + 1);
		}

		// check above tile
		if (i / m_columns != m_rows - 1)
		{
			assignWeight(i + m_columns);
		}

		// check below tile
		if (i / m_columns != 0)
		{
			assignWeight(i - m_columns);
		}
	}
}

void BoardManager::StartUp() 
{

}