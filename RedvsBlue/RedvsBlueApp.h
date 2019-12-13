#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Grid.h"
#include "BoardManager.h"

class RedvsBlueApp : public aie::Application {
public:

	RedvsBlueApp();
	virtual ~RedvsBlueApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	//Grid*				m_board;
	BoardManager*		m_board;
};