#pragma once
#include "GameObject.h"
#include <vector>
#include "Renderer2D.h"
#include "Input.h"
#include "Tile.h"
#include "Graph.h"
#include "GridMap.h"

class BoardManager
{
public:
	BoardManager();
	BoardManager(int c, int r, int t) : m_columns{ c }, m_rows{ r }, m_tileSize{ t } {};
	~BoardManager();

	void Start();
	void SetupScene(int level);
	void Print();
	void Draw(aie::Renderer2D* renderer);
	void Update(aie::Input* input);
	

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
	void InitialiseList();
	void ClearHoverList();
	void BuildNodeList();
	void BuildLandscape();
	void FillOutLevel();
	void PlaceUnits();
	void ShowMovementArea(Unit unit, Node* startNode);
	void DrawMovementArea(aie::Renderer2D* renderer);

private:
	int							m_columns;
	int							m_rows;
	Count*						m_waterTileCount;
	
	aie::Renderer2D*			m_2dRenderer;
	int							m_tileSize;
	int							m_leftBorder;
	int							m_bottomBorder;

	std::vector<ObjectType>		m_grid;
	std::vector<bool>			m_hover;
	// this list holds all the units on the board
	std::vector<Unit>			m_units;
	// combined the others lists into a weighted nodes
	std::vector<Node>			m_nodeList;

	Node*						m_startPoint;
	Node*						m_endPoint;

	std::list<const Node*>		m_path;
	int							m_lastSelectedUnit;
	std::list<const Node*>		m_movementArea;

	GridMap*					m_gridMap;
};

