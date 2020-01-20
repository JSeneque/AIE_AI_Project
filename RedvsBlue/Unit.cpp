#include "Unit.h"



Unit::Unit()
{
	m_gridIndex = -1;
	m_faction = Faction::NoFaction;
	m_hasMoved = false;
	m_state = eState::READY;
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
	m_hasMoved = true;
	setState(eState::EXHAUSTED);
}

void Unit::setFaction(Faction faction)
{
	m_faction = faction;
}

Faction Unit::getFaction()
{
	return m_faction;
}

void Unit::setHasMoved (bool value)
{ 
	m_hasMoved = value; 
}

bool Unit::getHasMoved()
{
	return m_hasMoved;
}
