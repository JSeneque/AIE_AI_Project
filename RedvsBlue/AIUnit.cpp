#include "AIUnit.h"


AIUnit::AIUnit()
{
	m_gridIndex = -1;
	m_faction = Faction::NoFaction;
	m_state = eState::READY;
	m_health = 10;
	m_attackStrength = 3;
	m_moveCost = 3;
}


AIUnit::~AIUnit()
{
}

int AIUnit::getPosition()
{
	return m_gridIndex;
}

void AIUnit::setPosition(int index)
{
	m_gridIndex = index;
}

void AIUnit::setFaction(Faction faction)
{
	m_faction = faction;
}

Faction AIUnit::getFaction()
{
	return m_faction;
}

// manages what happens when the unit shifts to the select state
void AIUnit::updateSelected()
{
	// if the unit is not exhausted, show where it is eligable to move too

}


void AIUnit::updateReady()
{


}

void AIUnit::updateExhausted()
{


}


void AIUnit::updateDead()
{

}

void AIUnit::updateAttack()
{

}
