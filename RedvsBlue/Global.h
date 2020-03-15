#pragma once
#include <iostream>

enum class Terrain {
	Ground = 0,
	Water
};
 
enum class Faction {
	NoFaction,
	RedFaction,
	BlueFaction
};

enum class eState { READY, SELECTED, EXHAUSTED, DEAD, ATTACK };


#define MAX_OBSERVERS 100

//void JN_Log(const char* text)
//{
//	std::cout << text << std::endl;
//}