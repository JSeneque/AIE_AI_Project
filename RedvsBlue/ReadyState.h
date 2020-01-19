#pragma once
#include "UnitState.h"
class ReadyState : public UnitState
{
public:
	ReadyState();
	~ReadyState();

	virtual void handleEvent(Unit& unit, State state) 
	{
		
	}
	virtual void update(Unit& unit) 
	{
	
	};
};



ReadyState::ReadyState()
{

}


ReadyState::~ReadyState()
{
}


