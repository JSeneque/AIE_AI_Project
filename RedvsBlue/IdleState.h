#pragma once
#include "AIUnitState.h"
#include "SearchForEnemyState.h"
#include "BoardManager.h"

class IdleState : public AIUnitState
{
public:
	IdleState() { };
	~IdleState();

	AIUnitState* setState(AIUnit& unit, aiState state) 
	{
		if (state == aiState::SEARCH)
		{
			std::cout << "AI Unit's state is now assigned to SEARCH state!" << std::endl;
			return new SearchForEnemyState();
		}

		return NULL;
	}

	virtual void update(BoardManager& bm, AIUnit& unit)
	{
		std::cout << "AI Unit's state is current in IDLE state!" << std::endl;
		std::cout << "Faction: " << (bm.getActiveFaction() == Faction::RedFaction ? "Red Faction" : "Blue Faction") << std::endl;
		if (bm.getActiveFaction() == Faction::RedFaction)
		{
			unit.state_ = new SearchForEnemyState();// &AIUnitState::search;
		}
	};


};




IdleState::~IdleState()
{
}

