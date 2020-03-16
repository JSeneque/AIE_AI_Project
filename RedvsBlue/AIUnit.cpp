#include "AIUnit.h"
#include "IdleState.h"

AIUnit::AIUnit()
{
	m_gridIndex = -1;
	m_faction = Faction::NoFaction;
	//m_state = eState::READY;
	state_ = new IdleState(); //SearchForEnemyState();
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




