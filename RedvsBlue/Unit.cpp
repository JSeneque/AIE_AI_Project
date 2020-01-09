#include "Unit.h"



Unit::Unit()
{
	m_gridIndex = -1;
	m_faction = NoFaction;
	/*m_isSelected = false;
	m_isActive = false;
	m_movementCost = 3;
	m_Team = NoTeam;*/
}


Unit::~Unit()
{
}

int Unit::getPosition()
{
	return m_gridIndex;
}

void Unit::setPosition(int index)
{
	m_gridIndex = index;
}

void Unit::setFaction(Faction faction)
{
	m_faction = faction;
}

Faction Unit::getFaction()
{
	return m_faction;
}

/*
void Unit::setIsSelected(bool flag)
{
	m_isSelected = flag;
}

void Unit::setActive(bool flag)
{
	m_isActive = flag;
}

void Unit::setTeam(Team team) {
	m_Team = team;
}
//
//Unit Unit::operator = (const Unit &other) {
//	m_movementCost = other.m_movementCost; 
//	m_isSelected = other.m_isSelected;
//	return *this;
//}
*/