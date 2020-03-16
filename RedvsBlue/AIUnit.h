#pragma once
#include "Global.h"
#include "Renderer2D.h"
#include "AIUnitState.h"
#include "BoardManager.h"
#include <iostream>
#include <assert.h>

class AIUnit
{
public:
	AIUnit();
	~AIUnit();

	int getPosition();
	void setPosition(int index);

	void setFaction(Faction faction);
	Faction getFaction();


	virtual void setState(aiState state)
	{


		state_->setState(*this, state);

		/*if (tempState != NULL)
		{
			delete state_;
			state_ = tempState;
		}*/

	}

	virtual void update(BoardManager& bm)
	{
		state_->update(bm, *this);
	}

	eState getState() { return m_state; }

	void takeDamage(int points)
	{
		m_health -= points;

		if (m_health <= 0)
		{
			//setState(aiState::DEAD);
		}
	}

	int getMoveCost()
	{
		return m_moveCost;
	}


	int getAttackStrength() { return m_attackStrength; }


private:
	int m_gridIndex;
	Faction m_faction;
	eState m_state;
	int m_health;
	int m_attackStrength;
	int m_moveCost;

public:

	AIUnitState* state_;

};

