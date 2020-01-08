#pragma once
enum class eGameState {
	SPLASH,
	INGAME,
	STATE_COUNT
};

const float PI = 3.14159265359;
const float RADIANS = PI / 180.0f;

const int PLAYER_STATE_CONTROLLED = 0;

const int ENEMY_STATE_PATROL = 0;
const int ENEMY_STATE_CHASE = 1;

const int OBJECT_STATE_CONTROLLED = 0;
const int NO_OF_METEORS = 15;
const int MAX_NO_OF_LASERS = 10;
const int MIN_Y = 100;
const int MAX_Y = 650;
const int MIN_X = 1400;
const int MAX_X = 2500;
const float OFFSCREEN_X = -100;
const float LASER_OFFSCREEN_X = 1400;
const float FIRE_WAIT = 0.5f;
const float INVINCIBLE = 5.0f;
const float BLINK_TIMER = 0.3f;

