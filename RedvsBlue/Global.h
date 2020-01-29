#pragma once
enum class Terrain {
	Ground = 0,
	Water
};
 
enum class Faction {
	NoFaction,
	RedFaction,
	BlueFaction
};

enum class eState { READY, SELECTED, EXHAUSTED, DEAD };


#define MAX_OBSERVERS 100

