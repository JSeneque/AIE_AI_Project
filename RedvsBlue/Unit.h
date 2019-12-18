#pragma once
#include "Global.h"

class Unit
{
public:
	Unit();
	~Unit();

	void setTeam(Team team);
	Team getTeam() { return m_Team; }

	void setIsSelected(bool flag);
	bool getIsSelected() { return m_isSelected; }

	void setActive(bool flag);
	bool getActive() { return m_isActive; }

	//void draw(aie::Renderer2D* renderer);

	//Unit operator = (const Unit &other);


private:
	int m_movementCost;
	bool m_isSelected;

	// I don't think this is the best options because the list is populated of units
	bool m_isActive;
	Team m_Team;
};

