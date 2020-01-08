#pragma once
enum ObjectType {
	Ground = 0,
	Water,
	Soldier,
	Tree
};
 
enum Team {
	NoTeam,
	Red,
	Blue
};

enum Event {
	UNIT_SELECTED
};


#define MAX_OBSERVERS 100

