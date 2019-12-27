#include "BoardManager.h"
#include <iostream>
#include "Dijkstra.h"
#include "Global.h"
#include <math.h>

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
	m_units.clear();

	m_grid.resize(m_columns * m_rows);
	m_hover.resize(m_columns * m_rows);
	m_units.resize(m_columns * m_rows);

	m_lastSelectedUnit = 999999;

	

}

void BoardManager::BuildLandscape()
{
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

			}
			else
			{
				m_grid.at(x + m_columns * y) = Ground;

			}
			m_hover.at(x + m_columns * y) = false;
		}
	}
}

void BoardManager::FillOutLevel()
{
	m_grid.at(44) = Water;
}

void BoardManager::SetupScene(int level)
{
	InitialiseList();
	BuildLandscape();
	FillOutLevel();
	PlaceUnits();
	BuildNodeList();

	// hardcoded for prototyping purposes
	m_startPoint = &m_nodeList[55];
	m_endPoint = &m_nodeList[58];

	//m_path = DijkstraSearch(m_startPoint, m_endPoint);
}

void BoardManager::Draw(aie::Renderer2D* renderer)
{
	// draw map
	for (int i = 0; i < m_grid.size(); ++i)
	{
		ObjectType objectType = m_grid.at(i);

		// screen coordinates
		int x = (i % m_columns) * m_tileSize + m_tileSize / 2;
		int y = (i / m_columns) * m_tileSize + m_tileSize / 2;

		switch (objectType)
		{
		case Ground:
			// 107,142,35)
			renderer->setRenderColour(0.42, 0.56, .01, 1);
			break;
		case Water:
			renderer->setRenderColour(0.20, 0.80, 1.0, 1);
			break;
		/*case Soldier:
			renderer->setRenderColour(0.42, 0.56, .01, 1);
			break;*/
		}

		if (m_hover.at(i))
		{
			// 154,205,50
			renderer->setRenderColour(0.6, 0.8, .20, 1);
		}

		renderer->drawBox(x, y, m_tileSize, m_tileSize);

		// draw movement
		if (m_lastSelectedUnit != 999999)
			DrawMovementArea(renderer);

		// draw soldier (refactor into unit class to draw)
		if (m_units[i].getActive())

		{
			// draw a circle at the starting position of the path
			float ax = i % m_columns;
			float ay = i / m_columns;

			if (m_units[i].getTeam() == Blue && !m_units[i].getIsSelected())
			{
				renderer->setRenderColour(0.42, 0.56, 1.0, 1);
			}
			else if (m_units[i].getTeam() == Red && !m_units[i].getIsSelected())
			{
				renderer->setRenderColour(1.0, 0.56, 0.42, 1);
			}
			else
			{
				renderer->setRenderColour(1.0, 1.0, 1.0, 1);
			}

			renderer->drawCircle(ax * m_tileSize + m_tileSize / 2, ay * m_tileSize + m_tileSize / 2, m_tileSize / 4);
		}
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

	//// set the path colour
	//renderer->setRenderColour(1, 0.5, 0.3, 1);

	//// check the path is not empty
	//if (m_path.size() > 2)
	//{
	//	// setup for loop with two initialisers
	//	for (auto i = m_path.begin(), j = std::next(m_path.begin()); j != m_path.end(); ++i, ++j)
	//	{
	//		// get the starting and ending points
	//		unsigned int id = (*i)->id;
	//		unsigned int jd = (*j)->id;
	//		float ix = (id % m_columns) * m_tileSize + m_tileSize / 2;
	//		float iy = (id / m_columns) * m_tileSize + m_tileSize / 2;
	//		float jx = (jd % m_columns) * m_tileSize + m_tileSize / 2;
	//		float jy = (jd / m_columns) * m_tileSize + m_tileSize / 2;

	//		// draw line
	//		renderer->drawLine(ix, iy, jx, jy, 4);

	//	}
	//}

	
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

	// detect a left click on a unit
	if (input->wasMouseButtonPressed(0))
	{
		
		// get the index where the left click occurs
		// get the mouse position in pixels and  convert into an index
		int x = input->getMouseX() / m_tileSize;
		int y = input->getMouseY() / m_tileSize;

		std::cout << "Debug: Left Click at x: " << x << " y: " << y << std::endl;

		// calculate the index from the x and y
		int index = x + y * m_columns;

		// there is a unit at that location and is not already selected
		if (m_units[index].getActive() && index != m_lastSelectedUnit)
		{
			// set the unit as selected
			m_units[index].setIsSelected(true);

			// draw a path to initiate the running cost to draw the movement area
			m_startPoint = &m_nodeList[index];

			/*if (x <= m_columns / 2)
				m_endPoint = &m_nodeList[m_columns + m_rows * m_columns];
		*/

			m_path = FanOutCalculateRunningCost(m_startPoint);

			if (m_lastSelectedUnit != 999999)
			{
				m_units[m_lastSelectedUnit].setIsSelected(false);
			}

			m_lastSelectedUnit = index;

			// show where the unit can move to
			// Absolute (unit.x - tile.x) + Absolute(unit.y - tile.y) <= Unit.MovementCost
			//ShowMovementArea(m_units[index], &m_nodeList[index]);
		} 
		else
		{
			if (m_lastSelectedUnit != 999999)
			{
				m_units[m_lastSelectedUnit].setIsSelected(false);
				m_lastSelectedUnit = 999999;
			}
		}

	}
	
	// debug to test distance formula
	if (input->wasMouseButtonPressed(1))
	{
		if (m_lastSelectedUnit != 999999)
		{
			int x = input->getMouseX() / m_tileSize;
			int y = input->getMouseY() / m_tileSize;

			int index = x + y * m_columns;

			m_endPoint = &m_nodeList[index];

			m_path = DijkstraSearch(m_startPoint, m_endPoint);
		}
	}
}

void BoardManager::ClearHoverList()
{
	for (auto& i : m_hover)
	{
		i = false;
	}
}

void BoardManager::PlaceUnits()
{
	Unit unit;
	m_units.at(55).setTeam(Red);
	m_units.at(55).setActive(true);
	m_units.at(58).setTeam(Blue);
	m_units.at(58).setActive(true);

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
			float weight = m_grid[id] == Water || m_grid[id] == Soldier  ? 1000000.0f : 1.0f;
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

void BoardManager::ShowMovementArea(Unit unit, Node* startNode)
{
	
}

void BoardManager::DrawMovementArea(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(0.65, 0.85, .01, 0.3);
	

	for (auto& i : m_nodeList)
	{
		if (i.runningCost < 4 && i.runningCost != 0)
		{
			int x = (i.id % m_columns) * m_tileSize + m_tileSize / 2;
			int y = (i.id / m_columns) * m_tileSize + m_tileSize / 2;

			renderer->drawBox(x, y, m_tileSize, m_tileSize);
		}
		
	}

}
