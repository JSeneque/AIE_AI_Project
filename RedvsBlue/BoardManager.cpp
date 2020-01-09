#include "BoardManager.h"
#include <iostream>
#include "Dijkstra.h"
#include "Global.h"
#include <math.h>
#include "GridMap.h"

std::list<const Node*> DijkstraSearch(Node* startNode, Node* endNode);

BoardManager::BoardManager()
{
	
}


BoardManager::~BoardManager()
{
}

//void BoardManager::Print()
//{
//	std::cout << "Board size: " << m_columns << " x " << m_rows << std::endl;
//	std::cout << "Grid size: " << m_grid.size() << std::endl;
//}
//
//void BoardManager::Start()
//{
//	// so if 5,9 mens  a minimum of 5 items and a maximum of 9
//	m_waterTileCount = new Count(5, 9);
//	
//}

void BoardManager::Initialise()
{
	m_gridMap = new GridMap(10, 10, 64);
	m_gridMap->CreateMap();
	m_gridMap->Print();

	//m_grid.clear();
	//m_units.clear();
/*
	m_grid.resize(m_columns * m_rows);*/
	m_hover.resize(m_columns * m_rows);
	//m_units.resize(m_columns * m_rows);

	m_lastSelectedUnit = 999999;

	
	

}

//void BoardManager::BuildLandscape()
//{
//	// set up outer water tiles
//	for (int x = 0; x < m_columns ; x++)
//	{
//		for (int y = 0; y < m_rows ; y++)
//		{
//			// if we are on the outer rim, draw water tile
//			if (x == 0 || x == m_columns - 1 || y == 0 || y == m_rows - 1)
//			{
//				// draw water tile
//				//m_grid.at(x + m_columns * y) = Water;
//				m_gridMap->setTileAt(x, y, Water);
//			}
//			else
//			{
//				//m_grid.at(x + m_columns * y) = Ground;
//				m_gridMap->setTileAt(x, y, Ground);
//			}
//			m_hover.at(x + m_columns * y) = false;
//		}
//	}
//}

//void BoardManager::FillOutLevel()
//{
//	m_grid.at(44) = Water;
//}

void BoardManager::SetupScene(int level)
{
	Initialise();
	//BuildLandscape();
	//FillOutLevel();
	//PlaceUnits();
	//BuildNodeList();

	// hardcoded for prototyping purposes
	//m_startPoint = &m_nodeList[55];
	//m_endPoint = &m_nodeList[58];

	//m_path = DijkstraSearch(m_startPoint, m_endPoint);
}

void BoardManager::Draw(aie::Renderer2D* renderer)
{
	// draw the map
	m_gridMap->draw(renderer);
	// show where mouse is
	m_gridMap->drawHover(renderer, mouseX, mouseY);
	// draw grid lines
	m_gridMap->drawGridLine(renderer);


		
		//// draw movement
		//if (m_lastSelectedUnit != 999999)
		//	DrawMovementArea(renderer);

		//// draw soldier (refactor into unit class to draw)
		//if (m_units[i].getActive())

		//{
		//	// draw a circle at the starting position of the path
		//	float ax = i % m_columns;
		//	float ay = i / m_columns;

		//	if (m_units[i].getTeam() == Blue && !m_units[i].getIsSelected())
		//	{
		//		renderer->setRenderColour(0.42, 0.56, 1.0, 1);
		//	}
		//	else if (m_units[i].getTeam() == Red && !m_units[i].getIsSelected())
		//	{
		//		renderer->setRenderColour(1.0, 0.56, 0.42, 1);
		//	}
		//	else
		//	{
		//		renderer->setRenderColour(1.0, 1.0, 1.0, 1);
		//	}

		//	renderer->drawCircle(ax * m_tileSize + m_tileSize / 2, ay * m_tileSize + m_tileSize / 2, m_tileSize / 4);
		//}
	//}


}


void BoardManager::Update(aie::Input* input)
{
	// highlight the grid cell the mouse is over
	mouseX = input->getMouseX();
	mouseY = input->getMouseY();

	UpdateUnits();
		
	// if the players clicks the left mouse button, is that grid cell occupied
	// 

	// detect a left click on a unit
	//if (input->wasMouseButtonPressed(0))
	//{
	//	
	//	// get the index where the left click occurs
	//	// get the mouse position in pixels and  convert into an index
	//	int x = input->getMouseX() / m_tileSize;
	//	int y = input->getMouseY() / m_tileSize;

	//	std::cout << "Debug: Left Click at x: " << x << " y: " << y << std::endl;

	//	// calculate the index from the x and y
	//	int index = x + y * m_columns;

	//	// there is a unit at that location and is not already selected
	//	if (m_units[index].getActive() && index != m_lastSelectedUnit)
	//	{
	//		// set the unit as selected
	//		m_units[index].setIsSelected(true);

	//		// draw a path to initiate the running cost to draw the movement area
	//		m_startPoint = &m_nodeList[index];

	//		/*if (x <= m_columns / 2)
	//			m_endPoint = &m_nodeList[m_columns + m_rows * m_columns];
	//	*/

	//		m_path = FanOutCalculateRunningCost(m_startPoint);

	//		if (m_lastSelectedUnit != 999999)
	//		{
	//			m_units[m_lastSelectedUnit].setIsSelected(false);
	//		}

	//		m_lastSelectedUnit = index;

	//		// show where the unit can move to
	//		// Absolute (unit.x - tile.x) + Absolute(unit.y - tile.y) <= Unit.MovementCost
	//		//ShowMovementArea(m_units[index], &m_nodeList[index]);
	//	} 
	//	else
	//	{
	//		if (m_lastSelectedUnit != 999999)
	//		{
	//			m_units[m_lastSelectedUnit].setIsSelected(false);
	//			m_lastSelectedUnit = 999999;
	//		}
	//	}

	//}
	
	//// debug to test distance formula
	//if (input->wasMouseButtonPressed(1))
	//{
	//	if (m_lastSelectedUnit != 999999)
	//	{
	//		int x = input->getMouseX() / m_tileSize;
	//		int y = input->getMouseY() / m_tileSize;

	//		int index = x + y * m_columns;

	//		m_endPoint = &m_nodeList[index];

	//		m_path = DijkstraSearch(m_startPoint, m_endPoint);
	//	}
	//}
}

void BoardManager::ClearHoverList()
{
	for (auto& i : m_hover)
	{
		i = false;
	}
}

void BoardManager::UpdateUnits()
{
	Unit unit;

	unit.setPosition(51);
	unit.setFaction(BlueFaction);
	m_gridMap->addUnit(unit);

	unit.setPosition(68);
	unit.setFaction(RedFaction);
	m_gridMap->addUnit(unit);

	std::cout << "Unit At(" << unit.getPosition() << ")" << std::endl;
	//m_units.at(55).setTeam(Red);
	//m_units.at(55).setActive(true);
	//m_units.at(58).setTeam(Blue);
	//m_units.at(58).setActive(true);

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
			//float weight = m_grid[id] == Water || m_grid[id] == Soldier  ? 1000000.0f : 1.0f;
			//m_nodeList[i].outgoingEdges.push_back(Edge{ &m_nodeList[id], weight });

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
