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

void BoardManager::Initialise()
{
	m_gridMap = new GridMap(10, 10, 64);
	m_gridMap->CreateMap();
	m_gridMap->Print();

	m_lastSelectedUnit = 999999;
}

void BoardManager::SetupScene(int level)
{
	Initialise();
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
	drawUnits(renderer);
	// show where mouse is
	m_gridMap->drawHover(renderer, mouseX, mouseY);
	// draw grid lines
	m_gridMap->drawGridLine(renderer);

}


void BoardManager::Update(aie::Input* input)
{
	// highlight the grid cell the mouse is over
	mouseX = input->getMouseX();
	mouseY = input->getMouseY();

	int index = m_gridMap->getGridIndex(mouseX, mouseY);

	UpdateUnits();
	bool check;

	check = m_gridMap->CheckBounds(mouseX, mouseY);

	// check within bounds
	

	// if the players clicks the left mouse button, is that grid cell occupied
	if (input->wasMouseButtonPressed(0))
	{
		// which grid cell was clicked on
		check = m_gridMap->CheckBounds(mouseX, mouseY);
		std::cout << "Screen X: " << mouseX << " Index: " << index << " Bounds: " << (check ? " YES" : " NO") << std::endl;
		// is there a unit in that cell

		// change the state of the unit to be selected
	}

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

void BoardManager::UpdateUnits()
{
	Unit unit;

	unit.setPosition(51);
	unit.setFaction(BlueFaction);
	addUnit(unit);

	unit.setPosition(68);
	unit.setFaction(RedFaction);
	addUnit(unit);

	//std::cout << "Unit At(" << unit.getPosition() << ")" << std::endl;

}

void BoardManager::drawUnits(aie::Renderer2D* renderer)
{
	// draw map
	for (int i = 0; i < m_units.size(); ++i)
	{
		int index = m_units[i].getPosition();
		// screen coordinates
		int x = m_gridMap->getScreenCoordinateX(index);
		int y = m_gridMap->getScreenCoordinateY(index);

		// set the unit colour
		Faction faction = m_units[i].getFaction();

		if (faction == BlueFaction)
			renderer->setRenderColour(0.42, 0.56, 1.0, 1);
		else if (faction == RedFaction)
			renderer->setRenderColour(1.0, 0.56, 0.42, 1);

		// draw unit
		renderer->drawCircle(x, y, m_gridMap->getGridSize() / 4);
	}
}

void BoardManager::addUnit(Unit unit)
{
	m_units.push_back(unit);
}


