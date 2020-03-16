#pragma once
#include "AIUnitState.h"
#include "AIUnit.h"

class SearchForEnemyState : public AIUnitState
{
public:
	SearchForEnemyState();
	~SearchForEnemyState();

	void onEnter();

	AIUnitState* setState(AIUnit& unit, aiState state)
	{
		return NULL;
	}

	virtual void update(BoardManager& bm, AIUnit& unit)
	{
		//std::cout << "Unit's state is currently in SEARCH state!" << std::endl;
	};
};

void SearchForEnemyState::onEnter()
{
	std::cout << "AI Unit entering SearchForEnemyState" << std::endl;
}



SearchForEnemyState::SearchForEnemyState()
{
	onEnter();

}


SearchForEnemyState::~SearchForEnemyState()
{
}
