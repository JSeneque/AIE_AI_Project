#pragma once
#include "UnitState.h"
#include <iostream>
#include "Global.h"
#include "ReadyState.h"

class SelectState : public UnitState
{
public:
	SelectState();
	~SelectState();

	UnitState* handleMessage(Unit& unit, eMessage message)
	{
		if (message == eMessage::READY)
		{
			std::cout << "Message received for ready!" << std::endl;
			return new ReadyState;
		}

		return NULL;
	}

	virtual void update(Unit& unit)
	{
		std::cout << "Select state!" << std::endl;
	};
};



SelectState::SelectState()
{

}


SelectState::~SelectState()
{
}