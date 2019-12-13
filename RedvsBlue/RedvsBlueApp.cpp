#include "RedvsBlueApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

RedvsBlueApp::RedvsBlueApp() {

}

RedvsBlueApp::~RedvsBlueApp() {

}

bool RedvsBlueApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	// create a 8x6 grid board
	//m_board = new Grid(8, 6);
	m_board = new BoardManager(10, 10, 64);
	m_board->SetupScene(1);
	// print out grid board to console as a debug
	m_board->Print();
	//m_board->InitialiseList();
	return true;
}

void RedvsBlueApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void RedvsBlueApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_board->Update(input);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void RedvsBlueApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_board->Draw(m_2dRenderer);
	
	// output some text, uses the last used colour
	//m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}