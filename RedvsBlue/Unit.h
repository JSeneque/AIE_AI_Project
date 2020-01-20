#pragma once
#include "Global.h"
#include "Renderer2D.h"
#include "UnitState.h"
#include <iostream>
#include <assert.h>
//class Faction
//{
//public:
//	std::string getName() const { return name; }
//	void setName(std::string name_) { name = name_; }
//
//	
//
//private:
//	std::string name;
//	
//
//};

class Unit
{
public:
	Unit();
	~Unit();

	int getPosition();
	void setPosition(int index);

	void setFaction(Faction faction);
	Faction getFaction();

	//void setHasMoved(bool value);
	//bool getHasMoved();
	
	void setState(eState state_) { m_state = state_; }
	eState getState() { return m_state; }

	void update()
	{
		switch (m_state)
		{
		case eState::READY: updateReady(); break;
		case eState::SELECTED: updateSelected(); break;
		case eState::EXHAUSTED: updateExhausted(); break;
		default: assert(false && "m_state is invalid");
		}
	}

private:
	void updateReady() { std::cout << "Unit in Ready State" << std::endl; }
	void updateSelected() { std::cout << "Unit in Selected State" << std::endl; }
	void updateExhausted() { std::cout << "Unit in Exhausted State" << std::endl; }

private:
	int m_gridIndex;
	Faction m_faction;
	//bool m_hasMoved;
	eState m_state;
	
};

