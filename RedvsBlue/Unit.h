#pragma once
#include "Global.h"
#include "Renderer2D.h"
#include <string>

class Faction
{
public:
	std::string getName() const { return name; }
	void setName(std::string name_) { name = name_; }

private:
	std::string name;

};

class Unit
{
public:
	Unit();
	~Unit();

	int getPosition();
	void setPosition(int index);

	void setFaction(std::string faction);
	std::string getFaction();

	void setHasMoved(bool value);
	bool getHasMoved();

private:
	int m_gridIndex;
	Faction m_faction;
	bool m_hasMoved;
	//Faction m_faction;
};

