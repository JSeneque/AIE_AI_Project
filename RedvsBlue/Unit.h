#pragma once
#include "Global.h"
#include "Renderer2D.h"

class Unit
{
public:
	Unit();
	~Unit();

	int getPosition();
	void setPosition(int index);

	void setFaction(Faction faction);
	Faction getFaction();

	void setHasMoved(bool value);
	bool getHasMoved();

private:
	int m_gridIndex;
	Faction m_faction;
	bool m_hasMoved;
};

