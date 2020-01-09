#pragma once
enum ObjectType {
	Ground = 0,
	Water,
	Soldier,
	Tree,
	Hover

};
 
enum Faction {
	NoFaction,
	RedFaction,
	BlueFaction
};

enum Event {
	UNIT_SELECTED
};


#define MAX_OBSERVERS 100

