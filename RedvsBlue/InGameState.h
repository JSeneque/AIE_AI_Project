#pragma once
#include "GameState.h"
#include "Renderer2D.h"
#include <Texture.h>

class Texture;

class InGameState : public GameState
{
public:
	InGameState() {}
	~InGameState() {}

	void onUpdate(float deltaTime);
	void onDraw(aie::Renderer2D* renderer);

	void onEnter();
	void onExit();
	void onPushed() {}
	void onPopped() {}
	Texture* loadTexture(const char * filename);

private:
	float					m_fireLaserTimer;
	float					m_invincibleTimer;
	float					m_blinkingTimer;
	bool					m_showHero;

	void setupHero();
	void setupPools();
	void createMeteor();
	void createLaser();
	void respawnHero();
};
