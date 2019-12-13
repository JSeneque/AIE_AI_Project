#pragma once
#include "GameObject.h"

class Tile : GameObject
{
public:
	Tile();
	~Tile();

	void setHoverOver(bool value);

private:
	bool isHovedOver;
};

