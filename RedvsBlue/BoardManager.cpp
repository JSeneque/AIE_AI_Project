#include "BoardManager.h"
#include <iostream>
#include "Dijkstra.h"
#include "Global.h"
#include <math.h>
#include "GridMap.h"
#include <algorithm>

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

	m_activeFaction = Faction::BlueFaction;

	m_selectedUnitIndex = -1;
	m_selectedUnit = nullptr;

	Unit unit;

	unit.setPosition(51);
	unit.setFaction(Faction::BlueFaction);
	addUnit(unit);

	unit.setPosition(61);
	unit.setFaction(Faction::BlueFaction);
	addUnit(unit);
	
	AIUnit aiUnit;

	aiUnit.setPosition(68);
	aiUnit.setFaction(Faction::RedFaction);
	m_aiUnits.push_back(aiUnit);

	aiUnit.setPosition(48);
	aiUnit.setFaction(Faction::RedFaction);
	m_aiUnits.push_back(aiUnit);
}

void BoardManager::SetupScene(int level)
{
	Initialise();
	BuildNodeList();
}

void BoardManager::BuildNodeList()
{
	int map_x_dim = m_gridMap->getGridSizeColumns();
	int map_y_dim = m_gridMap->getGridSizeRows();

	// clears the node list
	m_nodeList.clear();
	// specifying the size of the grid
	m_nodeList.resize(m_gridMap->getGridSize());
	// initialise each node
	for (int i = 0; i < m_nodeList.size(); ++i)
	{
		// set id
		m_nodeList[i].id = i;
		auto assignWeight = [&](int id) {
			float weight = m_gridMap->getGridMapTile(i) == Terrain::Water ? 1000000.0f : 1.0f;
			m_nodeList[i].outgoingEdges.push_back(Edge{ &m_nodeList[id], weight });
		};
		// check if we can add to the left
		if (i%map_x_dim != 0)
		{
			assignWeight(i - 1);
		}
		// check if we can add to the right
		if ((i + 1) % map_x_dim != 0)
		{
			assignWeight(i + 1);
		}
		// check if we can add to the top
		if (i / map_x_dim != map_y_dim - 1)
		{
			assignWeight(i + map_x_dim);
		}
		// check if we can add to the bottom
		if (i / map_x_dim != 0)
		{
			assignWeight(i - map_x_dim);
		}

	}

}

void BoardManager::Draw(aie::Renderer2D* renderer)
{
	// draw the map
	m_gridMap->draw(renderer);
	drawUnits(renderer);

	
	// draw grid lines
	m_gridMap->drawGridLine(renderer);

	if (m_selectedUnit) 
	{
		drawTileBorder(renderer);
	}

	// show where mouse is
	m_gridMap->drawHover(renderer, mouseX, mouseY);
	

}


void BoardManager::Update(aie::Input* input)
{
	// check that all the units of the active faction had their turn
	// if yes, set the new turn to the other faction
	// reset all units of active faction to 'Ready'state
	CheckTurn();
	UpdateUnits();
	
	// determine if player or AI
	if (m_activeFaction == Faction::BlueFaction)
	{
		//std::cout << "Player Turn" << std::endl;
		HandleMouseInput(input);
	}
	else
	{
		//std::cout << "Process AI Turn" << std::endl;
		ProcessAI();
	}

	

	// process player move turn function...if blue...handle mouse input, red do ai function
}
	

void BoardManager::drawUnits(aie::Renderer2D* renderer)
{
	// draw player units
	for (int i = 0; i < m_units.size(); ++i)
	{
		int index = m_units[i].getPosition();
		// screen coordinates
		int x = m_gridMap->getScreenCoordinateX(index);
		int y = m_gridMap->getScreenCoordinateY(index);

		// set the unit colour
		//Faction faction = m_units[i].getFaction();

		if (m_units[i].getFaction() == Faction::BlueFaction)
			renderer->setRenderColour(0.42, 0.56, 1.0, 1);
		else 
			renderer->setRenderColour(1.0, 0.56, 0.42, 1);

		// draw unit
		renderer->drawCircle(x, y, m_gridMap->getGridSize() / 4);
	}

	// draw ai units
	for (int i = 0; i < m_aiUnits.size(); ++i)
	{
		int index = m_aiUnits[i].getPosition();
		// screen coordinates
		int x = m_gridMap->getScreenCoordinateX(index);
		int y = m_gridMap->getScreenCoordinateY(index);

		// set the unit colour
		//Faction faction = m_units[i].getFaction();

		if (m_aiUnits[i].getFaction() == Faction::BlueFaction)
			renderer->setRenderColour(0.42, 0.56, 1.0, 1);
		else
			renderer->setRenderColour(1.0, 0.56, 0.42, 1);

		// draw unit
		renderer->drawCircle(x, y, m_gridMap->getGridSize() / 4);
	}
}

void BoardManager::drawTileBorder(aie::Renderer2D* renderer)
{

	int m_tileSize = m_gridMap->getTileSize();

	renderer->setRenderColour(0, 1, 0, 1);

	float lineThickness = 5.0f;

	for (auto& node : m_path)
	{
		if (node->runningCost <= m_selectedUnit->getMoveCost() && m_gridMap->getGridMapTile(node->id) != Terrain::Water)
		{
			int screenX = m_gridMap->getScreenCoordinateX(node->id);
			int screenY = m_gridMap->getScreenCoordinateY(node->id);

			// top left horizontal line
			renderer->drawLine(screenX - (m_tileSize / 2), screenY - (m_tileSize / 2) + m_tileSize, (screenX + (m_tileSize * 0.25)) - (m_tileSize / 2), screenY - (m_tileSize / 2) + m_tileSize, lineThickness);
			// top right horizontal line
			renderer->drawLine(screenX + (m_tileSize * 0.25), screenY - (m_tileSize / 2) + m_tileSize, screenX + (m_tileSize / 2), screenY - (m_tileSize / 2) + m_tileSize, lineThickness);

			// bottom left horizontal line
			renderer->drawLine(screenX - (m_tileSize / 2), screenY - (m_tileSize / 2), (screenX + (m_tileSize * 0.25)) - (m_tileSize / 2), screenY - (m_tileSize / 2), lineThickness);
			// bottom right horizontal line
			renderer->drawLine(screenX + (m_tileSize * 0.25), screenY - (m_tileSize / 2), screenX + (m_tileSize / 2), screenY - (m_tileSize / 2), lineThickness);

			// top left vertical line
			renderer->drawLine(screenX - (m_tileSize / 2), screenY - (m_tileSize / 2) + m_tileSize, screenX - (m_tileSize / 2), screenY - (m_tileSize / 2) + m_tileSize - (m_tileSize * 0.25), lineThickness);

			// top right vertical line
			renderer->drawLine(screenX + (m_tileSize * 0.5), screenY - (m_tileSize / 2) + m_tileSize, screenX + (m_tileSize / 2), screenY - (m_tileSize / 2) + m_tileSize - (m_tileSize * 0.25), lineThickness);

			// bottom left vertical line
			renderer->drawLine(screenX - (m_tileSize / 2), screenY - (m_tileSize / 2), screenX - (m_tileSize / 2), screenY - (m_tileSize / 2) + (m_tileSize * 0.25), lineThickness);

			// bottom right vertical line
			renderer->drawLine(screenX + (m_tileSize * 0.5), screenY - (m_tileSize / 2), screenX + (m_tileSize / 2), screenY - (m_tileSize / 2) + (m_tileSize * 0.25), lineThickness);
		}

	}
}
	

void BoardManager::addUnit(Unit unit)
{
	m_units.push_back(unit);
}

// expensive but simplified version first
bool BoardManager::isUnitThere(int index)
{

	// check each unit's position
	for (auto& unit : m_units)
	{
		// 1. check if there is a unit there
		if (unit.getPosition() == index)
		{
			return true;
		}
	}
	return false;
}
	

void BoardManager::CheckTurn() 
{
	bool allMoved = true;
	// get each of the units
	for (auto& unit : m_units)
	{
		// if all units has moved, change the action faction
		if (unit.getState() != eState::EXHAUSTED && unit.getFaction() == m_activeFaction)
		{
			allMoved = false;
		}
	}
	
	if (allMoved)
	{
		ChangeTurn();
	}
}

void BoardManager::ChangeTurn() 
{
	// change faction's turn
	m_activeFaction = (m_activeFaction == Faction::BlueFaction ? Faction::RedFaction : Faction::BlueFaction);

	// reset all the units to ready state
	for (auto& unit : m_units)
	{
		// if all units has moved, change the action faction
		if (unit.getFaction() == m_activeFaction && unit.getState() != eState::DEAD)
		{
			//unit.setHasMoved(false);
			unit.setState(eState::READY);
		}
	}
}

void BoardManager::UpdateUnits()
{
	int pos = 0;

	for (auto& unit : m_units)
	{
		if (unit.getState() == eState::DEAD)
			m_units.erase(m_units.begin() + pos);
		pos++;
	}

	for (auto& unit : m_units)
	{
		unit.update();
	}

	pos = 0;

	for (auto& aiUnit : m_aiUnits)
	{
		if (aiUnit.getState() == eState::DEAD)
			m_aiUnits.erase(m_aiUnits.begin() + pos);
		pos++;
	}

	for (auto& aiUnit : m_aiUnits)
	{
		aiUnit.update();
	}
	
	

}

void BoardManager::ProcessClickedArea(int index)
{
	/*
		1. Did the player select an empty grid
		2. Did the player select a friendly unit
		3. If a unit is already selected, did the player choose to move it
		4. if a unit is already selected, did the player choose to attack an AI unit

	*/
	// check the clicked area was in bounds
	if (m_gridMap->CheckBounds(mouseX, mouseY))
	{
		// did the player select a different player unit
		for (auto& unit : m_units)
		{
			// 1. check if there is a unit there
			if (unit.getPosition() == index && unit.getState() != eState::DEAD)
			{
				//std::cout << "Selected a unit!" << std::endl;
				// if not unit currently selected, then select unit
				if (m_selectedUnit == nullptr && unit.getState() != eState::EXHAUSTED)
				{
					// save the unit
					m_selectedUnit = &unit;
					m_selectedUnit->setState(eState::SELECTED);
					m_path = ShowMovementArea(&m_nodeList[unit.getPosition()]);
					return;
				}
				else if (m_selectedUnit != nullptr)
				{
					m_selectedUnit->setState(eState::READY);
					// save the unit
					m_selectedUnit = &unit;
					// change the state of the unit
					unit.setState(eState::SELECTED);
					// build the areas the unit can move too
					m_path = ShowMovementArea(&m_nodeList[unit.getPosition()]);
					return;
				}
			}
		}

		// check if the player is attacking
		if (m_selectedUnit != nullptr)
		{
			for (auto& aiUnit : m_aiUnits)
			{
				// 1. check if there is a unit there
				if (aiUnit.getPosition() == index)//&& aiUnit.getState() != eState::DEAD)
				{
					std::cout << "Attacking!" << std::endl;
					AttackAIUnit(aiUnit, index);
					return;
				}
			}
		}

		// If we have a unit already select, is this cell valid
		if (m_selectedUnit != nullptr && validateMove(index))
		{
			MoveUnit(*m_selectedUnit, index);
		}

	}
}


void BoardManager::AttackUnit(Unit& unit, int index)
{
	m_selectedUnit->setState(eState::ATTACK);
	unit.takeDamage(m_selectedUnit->getAttackStrength());
	m_selectedUnit->setState(eState::EXHAUSTED);
	m_selectedUnit = nullptr;
}

void BoardManager::AttackAIUnit(AIUnit& unit, int index)
{
	m_selectedUnit->setState(eState::ATTACK);
	unit.takeDamage(m_selectedUnit->getAttackStrength());
	m_selectedUnit->setState(eState::EXHAUSTED);
	m_selectedUnit = nullptr;
}

void BoardManager::MoveUnit(Unit& unit, int index)
{
	m_selectedUnit->setPosition(index);
	m_selectedUnit->setState(eState::EXHAUSTED);
	m_selectedUnit = nullptr;
}

void BoardManager::MoveAIUnit(AIUnit& unit, int index)
{
	m_selectedAIUnit->setPosition(index);
	m_selectedAIUnit->setState(eState::EXHAUSTED);
	m_selectedAIUnit = nullptr;
}

void BoardManager::HandleMouseInput(aie::Input* input)
{
	// highlight the grid cell the mouse is over
	mouseX = input->getMouseX();
	mouseY = input->getMouseY();

	int index = m_gridMap->getGridIndex(mouseX, mouseY);

	//bool check;

	// if the players clicks the left mouse button, is that grid cell occupied
	if (input->wasMouseButtonPressed(0))
	{
		ProcessClickedArea(index);
	}
	
}

// checks in the grid cell selected is within the movement cost of the unit
bool BoardManager::validateMove(int index) 
{
	// is there a better, more optmised way to perform this, instead of check each node
	if (m_path.size() > index)
	{
		for (auto& node : m_path)
		{
			if (node->id == index && node->runningCost <= m_selectedUnit->getMoveCost())
			{
				std::cout << "Valid Location" << std::endl;
				return true;
			}
		}
	}
	std::cout << "Invalid Location" << std::endl;
	return false;
}

void BoardManager::ProcessAI()
{
	// 1. For each Ready AI Unit
		// 2. Find the closest enemy unit
		// 3. if the enemy unit is within range, attack it
		// 4. if the enemy unit is out of range, move to the tile closest to the enemy unit

	for (auto&aiUnit : m_aiUnits)
	{
		if (aiUnit.getFaction() == m_activeFaction && aiUnit.getState() == eState::READY)
		{
			m_selectedAIUnit = &aiUnit;
			std::cout << "Ready to process a READY AI unit!" << std::endl;
			// loop through each of the enemy units and determine which has the lowest running cost
			// determine start node
			m_startPoint = &m_nodeList[aiUnit.getPosition()];

			// find which enemy is the closest
			int runningCost = 9999;
			Unit* enemyUnit;

			for (auto&enemy : m_units)
			{
				if (enemy.getFaction() != m_activeFaction && enemy.getState() != eState::DEAD)
				{
					m_endPoint = &m_nodeList[enemy.getPosition()];
					// we have the path to the enemy unit
					m_path = DijkstraSearch(m_startPoint, m_endPoint);
					// is this the closest unit? I would like to move to a more spacial checking if I have time
					
					if (runningCost > m_path.back()->runningCost)
					{
						enemyUnit = &enemy;
						runningCost = m_path.back()->runningCost;
					}
				}
			}
			
			// if the enemy closest enough to attack or do we move to it
			if (runningCost <= aiUnit.getMoveCost())
			{
				// attack it
				AttackUnit(*enemyUnit, enemyUnit->getPosition()); // we don't rea
			}
			else
			{
				int index = 0;
				for (auto&node : m_path)
				{
					
					// the has to be a smarter way. Cycle through the path to the node we can move to limited by the move cost
					if (node->runningCost <= aiUnit.getMoveCost())
					{
						index = node->id;
					}
				}
				MoveAIUnit(aiUnit, index);
			}
		}
	}

}

