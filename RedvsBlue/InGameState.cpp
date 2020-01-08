#include "InGameState.h"
#include "GameDefs.h"
#include <iostream>
#include "Input.h"


void InGameState::onEnter() {
	setupHero();
	setupPools();
	//setupMeteor();
	m_fireLaserTimer = FIRE_WAIT;
	m_invincibleTimer = INVINCIBLE;
	m_blinkingTimer = BLINK_TIMER;
	m_showHero = true;
}

void InGameState::onExit() {
	delete m_hero;
	//delete m_meteor;
	delete m_meteorPool;
}

void InGameState::onUpdate(float deltaTime) {
	aie::Input* input = aie::Input::getInstance();

	m_hero->update(deltaTime);

	for (int i = 0; i < m_meteorPool->getCurrent(); i++) {
		m_meteorPool->getAt(i)->update(deltaTime);

		// if the meteor has reached the the other side of the screen, put it back into pool
		if (m_meteorPool->getAt(i)->getPosition().x < OFFSCREEN_X) {
			m_meteorPool->restore(m_meteorPool->getAt(i));
		}
	}


	// TODO: check if there is any meteors available in the pool
	if (m_meteorPool->getCurrent() < m_meteorPool->getMax()) {
		createMeteor();
	}

	// update next fire
	m_fireLaserTimer -= deltaTime;
	if (m_fireLaserTimer < 0)
		m_fireLaserTimer = 0;

	if (input->isKeyDown(aie::INPUT_KEY_SPACE) && m_fireLaserTimer == 0) {
		createLaser();
		m_fireLaserTimer = FIRE_WAIT;
	}

	for (int i = 0; i < m_laserPool->getCurrent(); i++) {
		m_laserPool->getAt(i)->update(deltaTime);

		// if the laser has reached the the other side of the screen, put it back into pool
		if (m_laserPool->getAt(i)->getPosition().x > LASER_OFFSCREEN_X) {
			m_laserPool->restore(m_laserPool->getAt(i));
		}
	}

	// check if laser colliders with any meteors
	for (int i = 0; i < m_meteorPool->getCurrent(); i++) {
		for (int j = 0; j < m_laserPool->getCurrent(); j++) {
			if (m_laserPool->getAt(j)->checkCollideWith(*m_meteorPool->getAt(i))) {
				m_meteorPool->restore(m_meteorPool->getAt(i));
				m_laserPool->restore(m_laserPool->getAt(j));
			}

		}
	}


	// check if hero colliders with any meteors 
	// TODO: move this to update. only here for colour red on draw
	if (!m_hero->getInvincible()) {
		for (int i = 0; i < m_meteorPool->getCurrent(); i++) {
			if (m_hero->checkCollideWith(*m_meteorPool->getAt(i))) {
				//renderer->setRenderColour(1, 0, 0, 1.0f);
				m_hero->setInvincible();
				respawnHero();
			}
		}
	}
	else {
		m_invincibleTimer -= deltaTime;
		m_blinkingTimer -= deltaTime;

		if (m_blinkingTimer < 0)
			m_blinkingTimer = 0;

		if (m_blinkingTimer == 0) {
			m_showHero = (m_showHero == true ? false : true);
			m_blinkingTimer = BLINK_TIMER;
		}

		if (m_invincibleTimer < 0)
			m_invincibleTimer = 0;

		if (m_invincibleTimer == 0) {
			m_hero->setInvincible();
			m_invincibleTimer = INVINCIBLE;
			m_showHero = true;
		}



	}

}

void InGameState::onDraw(aie::Renderer2D* renderer) {
	// draw hero
	if (m_showHero)
		m_hero->draw(renderer);

	// draw meteors
	for (int i = 0; i < m_meteorPool->getCurrent(); i++) {
		m_meteorPool->getAt(i)->draw(renderer);
	}

	// draw lasers
	for (int i = 0; i < m_laserPool->getCurrent(); i++) {
		m_laserPool->getAt(i)->draw(renderer);
	}
}

void InGameState::setupHero() {
	m_hero = new Hero();

	std::shared_ptr<aie::Texture> frame1 =
		std::make_shared<aie::Texture>("../bin/textures/SpaceFlier_lg_1.png");
	std::shared_ptr<aie::Texture> frame2 =
		std::make_shared<aie::Texture>("../bin/textures/SpaceFlier_lg_2.png");

	m_hero->addFrame(frame1, 0.15f);
	m_hero->addFrame(frame2, 0.15f);
	m_hero->setPosition({ 300, 300 });
	m_hero->setRadius(45);
}

void InGameState::setupPools() {
	/********* Meteors ***********/
	m_meteorPool = new ObjectPool<Meteor>(NO_OF_METEORS);

	for (int i = 0; i < m_meteorPool->getMax(); i++)
	{
		createMeteor();
	}

	/********* Lasers ***********/
	m_laserPool = new ObjectPool<LaserBeam>(MAX_NO_OF_LASERS);
}

void InGameState::createMeteor() {
	std::shared_ptr<aie::Texture> meteorFrame =
		std::make_shared<aie::Texture>("../bin/textures/asteroid.png");

	Meteor*	meteor = m_meteorPool->get();

	if (meteor != NULL)
	{
		meteor->addFrame(meteorFrame, 1);
		meteor->init();
		//TODO: Change this when you introduce factory pattern. d
		// speed and radius will suit size of meteor
		meteor->setSpeed(150);
		meteor->setRadius(45);
	}
}

void InGameState::createLaser() {
	std::shared_ptr<aie::Texture> laserFrame =
		std::make_shared<aie::Texture>("../bin/textures/laserbeam_blue.png");

	// get the hero position
	Vector2D pos = m_hero->getPosition();
	pos += Vector2D{ 100, 0.0f };

	LaserBeam*	laser = m_laserPool->get();
	if (laser != NULL)
	{
		laser->addFrame(laserFrame, 1);
		laser->setPosition({ pos.x, pos.y });
		laser->setSpeed(10);
		laser->setRadius(5);
	}
}

void InGameState::respawnHero() {
	m_hero->setPosition({ 300, 300 });

}

