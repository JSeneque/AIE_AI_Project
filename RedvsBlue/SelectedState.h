#pragma once
#include "UnitState.h"
#include "Global.h"
#include "ReadyState.h"
#include <iostream>


class SelectedState : public UnitState
{
public:
	SelectedState();
	~SelectedState();

	virtual UnitState* setState(Unit& unit, eState state)
	{
		if (state == eState::READY)
		{

			std::cout << "Unit's state is now assigned to READY state!" << std::endl;
			return NULL;// new ReadyState();
		}

		return NULL;
	}

	virtual void update(Unit& unit)
	{

	};
};



SelectedState::SelectedState()
{

}


SelectedState::~SelectedState()
{
}

