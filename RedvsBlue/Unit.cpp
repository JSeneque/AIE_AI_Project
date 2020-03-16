#include "Unit.h"



Unit::Unit()
{
	m_gridIndex = -1;
	m_faction = Faction::NoFaction;
	m_state = eState::READY;

	m_health = 10;
	m_attackStrength = 3;
	m_moveCost = 3;
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

// manages what happens when the unit shifts to the select state
void Unit::updateSelected()
{
	// if the unit is not exhausted, show where it is eligable to move too

}


void Unit::updateReady()
{


}

void Unit::updateExhausted()
{


}


void Unit::updateDead()
{

}

void Unit::updateAttack()
{

}

