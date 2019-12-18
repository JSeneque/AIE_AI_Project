#include "Unit.h"



Unit::Unit()
{
	m_isSelected = false;
	m_isActive = false;
	m_movementCost = 3;
	m_Team = NoTeam;
}


Unit::~Unit()
{
}

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
