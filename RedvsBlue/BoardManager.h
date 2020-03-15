#pragma once
#include "GameObject.h"
#include <vector>
#include "Renderer2D.h"
#include "Input.h"
#include "Tile.h"
#include "Graph.h"
#include "GridMap.h"
#include "AIUnit.h"

class BoardManager
{
public:
	BoardManager();
	~BoardManager();

	void SetupScene(int level);
	void Draw(aie::Renderer2D* renderer);
	void Update(aie::Input* input);
	void addUnit(Unit unit);
	

	// acts as a range
	class Count
	{
	public:
		Count(int min, int max) : minimum{ min }, maximum{ max }{};
	public :
		int minimum;
		int maximum;
	};

private:
	void Initialise();
	void UpdateUnits();
	void drawUnits(aie::Renderer2D* renderer);
	bool isUnitThere(int index);
	void CheckTurn();
	void ChangeTurn();
	void HandleMouseInput(aie::Input* input);
	void BuildNodeList();
	void drawTileBorder(aie::Renderer2D* renderer);
	bool validateMove(int index);
	void ProcessClickedArea(int index);
	void AttackUnit(Unit& unit, int index);
	void AttackAIUnit(AIUnit& unit, int index);
	void MoveUnit(Unit& unit, int index);
	void MoveAIUnit(AIUnit& unit, int index);
	void ProcessAI();

private:
	aie::Renderer2D*			m_2dRenderer;
	int							mouseX;
	int							mouseY;
	std::vector<Node>			m_nodeList;

	Node*						m_startPoint;
	Node*						m_endPoint;

	std::list<const Node*>		m_path;
	std::list<const Node*>		m_movementArea;

	GridMap*					m_gridMap;
	std::vector<Unit>			m_units;
	std::vector<AIUnit>			m_aiUnits;
	int							m_selectedUnitIndex;
	Unit*						m_selectedUnit;
	AIUnit*						m_selectedAIUnit;
	Faction						m_activeFaction;
};

