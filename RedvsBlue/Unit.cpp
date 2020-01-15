#include "Unit.h"



Unit::Unit()
{
	m_gridIndex = -1;
	m_faction = NoFaction;

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

