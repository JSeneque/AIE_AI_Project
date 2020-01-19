#include "Unit.h"



Unit::Unit()
{
	m_gridIndex = -1;
	m_faction.setName("NoFaction");
	m_hasMoved = false;
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
}

void Unit::setFaction(std::string name)
{
	m_faction.setName(name);
}

std::string Unit::getFaction()
{
	return m_faction.getName();
}

void Unit::setHasMoved (bool value)
{ 
	m_hasMoved = value; 
}

bool Unit::getHasMoved()
{
	return m_hasMoved;
}
