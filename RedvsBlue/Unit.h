#pragma once
#include "Global.h"
#include "Renderer2D.h"
#include "UnitState.h"
#include <iostream>
#include <assert.h>

class Unit
{
public:
	Unit();
	~Unit();

	int getPosition();
	void setPosition(int index);

	void setFaction(Faction faction);
	Faction getFaction();

	/*void setState(eState state_) {
			m_state = state_;
			switch (m_state)
			{
			case eState::READY: std::cout << "Unit in Ready State" << std::endl; break;
			case eState::SELECTED: std::cout << "Unit in Selected State" << std::endl; break;
			case eState::EXHAUSTED: std::cout << "Unit in Exhausted State" << std::endl; break;
			case eState::DEAD: std::cout << "Unit in Dead State" << std::endl; break;
			case eState::ATTACK: std::cout << "Unit in Attack State" << std::endl; break;
			default: assert(false && "m_state is invalid");
			}
	}*/

	void setState(eState input)
	{
		m_state = input;

		UnitState* state = state_->setState(*this, input);
		if (state != NULL)
		{
			delete state_;
			state_ = state;
		}
	}

	eState getState() { return m_state; }

	void takeDamage(int points)
	{ 
		m_health -= points;

		if (m_health <= 0)
		{
			setState(eState::DEAD);
		}
	}

	int getMoveCost()
	{
		return m_moveCost;
	}

	//void update()
	//{
	//	switch (m_state)
	//	{
	//	case eState::READY: updateReady(); break;
	//	case eState::SELECTED: updateSelected(); break;
	//	case eState::EXHAUSTED: updateExhausted(); break;
	//	case eState::DEAD: updateDead(); break;
	//	case eState::ATTACK: updateAttack(); break;
	//	default: assert(false && "m_state is invalid");
	//	}
	//}

	virtual void update()
	{
		state_->update(*this);
	}

	int getAttackStrength() { return m_attackStrength; }

private:
	void updateReady();
	void updateSelected();
	void updateExhausted();
	void updateDead();
	void updateAttack();

private:
	int m_gridIndex;
	Faction m_faction;
	eState m_state;
	int m_health;
	int m_attackStrength;
	int m_moveCost;
	
public:
	UnitState* state_;
	
};

