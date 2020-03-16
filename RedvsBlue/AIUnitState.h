#pragma once
//#include "Unit.h"
#include "Global.h"

class AIUnit;
class IdleState;
class SearchForEnemyState;
class BoardManager;

class AIUnitState
{
public:
	static IdleState idle;
	static SearchForEnemyState search;

	virtual ~AIUnitState() {}
	virtual AIUnitState* setState(AIUnit& unit, aiState state)  = 0;
	virtual void update(BoardManager& bm, AIUnit& unit) {};


};