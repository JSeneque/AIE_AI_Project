#include "Tile.h"



Tile::Tile()
{
	isHovedOver = false;
}


Tile::~Tile()
{
}

void Tile::setHoverOver(bool value)
{
	isHovedOver = value;
}
