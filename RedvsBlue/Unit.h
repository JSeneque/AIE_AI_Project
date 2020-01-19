#pragma once
#include "Global.h"
#include "Renderer2D.h"
#include <string>
#include "UnitState.h"

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

	void setHasMoved(bool value);
	bool getHasMoved();

	virtual void handleEvent(Unit& unit, State state)
	{
		state_->handleEvent(*this, state);
	}

	virtual void update()
	{
		state_->update(*this);
	}

public:
	UnitState * state_;
private:
	int m_gridIndex;
	Faction m_faction;
	bool m_hasMoved;
	
};

