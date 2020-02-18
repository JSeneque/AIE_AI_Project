#pragma once
//#include "Unit.h"
//#include "Global.h"
class Unit;
class ReadyState;
class SelectedState;

class UnitState
{
public:
	static ReadyState ready;
	static SelectedState selected;

	virtual ~UnitState() {}
	virtual UnitState* setState(Unit& unit, eState state)  = 0;
	virtual void update(Unit& unit) {};
};