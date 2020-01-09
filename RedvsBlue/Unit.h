#pragma once
#include "Global.h"
#include "Renderer2D.h"

class Unit
{
public:
	Unit();
	~Unit();

	int getPosition();
	void setPosition(int index);

	void setFaction(Faction faction);
	Faction getFaction();
	//void draw(aie::Renderer2D* renderer);

	/*
	void setTeam(Team team);
	Team getTeam() { return m_Team; }

	void setIsSelected(bool flag);
	bool getIsSelected() { return m_isSelected; }

	void setActive(bool flag);
	bool getActive() { return m_isActive; }

	int getMovementCost() { return m_movementCost; }
	*/
	//void draw(aie::Renderer2D* renderer);

	//Unit operator = (const Unit &other);


private:
	int m_gridIndex;
	Faction m_faction;

	/*
	int m_movementCost;
	bool m_isSelected;

	// I don't think this is the best options because the list is populated of units
	bool m_isActive;
	Team m_Team;
	*/
};

