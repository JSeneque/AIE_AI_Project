#pragma once
class Unit;
class ReadyState;

enum State {
	STATE_READY,
	STATE_SELECTED,
	STATE_EXHAUSED
};

class UnitState
{
public:
	static ReadyState ready;

	virtual ~UnitState() {}
	virtual void handleEvent(Unit& unit, State state) {}
	virtual void update(Unit& unit) {};
};