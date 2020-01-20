#pragma once
enum ObjectType {
	Ground = 0,
	Water,
	Soldier,
	Tree,
	Hover

};
 
enum class Faction {
	NoFaction,
	RedFaction,
	BlueFaction
};

enum class eState { READY, SELECTED, EXHAUSTED };


#define MAX_OBSERVERS 100

