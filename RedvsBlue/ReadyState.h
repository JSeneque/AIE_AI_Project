#pragma once
#include "UnitState.h"
#include "Global.h"
#include "SelectedState.h"
#include <iostream>

class ReadyState : public UnitState
{
public:
	ReadyState();
	~ReadyState();

	virtual UnitState* setState(Unit& unit, eState state) 
	{
		if (state == eState::SELECTED)
		{
			std::cout << "Unit's state is now assigned to SELECT state!" << std::endl;
			return new SelectedState();
		}

		return NULL;
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


