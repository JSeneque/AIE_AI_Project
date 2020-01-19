#pragma once
class Unit;

enum State {
	STATE_READY,
	STATE_SELECTED,
	STATE_USED_ACTION
};

class UnitState
{
public:
	virtual ~UnitState() {}
	virtual void handleEvent(Unit& unit, State state) {}
	virtual void onUpdate(Unit& unit) {};
};