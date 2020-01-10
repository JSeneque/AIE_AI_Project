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
	~BoardManager();

	void SetupScene(int level);
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
	void Initialise();
	void UpdateUnits();

private:
	aie::Renderer2D*			m_2dRenderer;
	int							mouseX;
	int							mouseY;
	std::vector<Node>			m_nodeList;

	Node*						m_startPoint;
	Node*						m_endPoint;

	std::list<const Node*>		m_path;
	int							m_lastSelectedUnit;
	std::list<const Node*>		m_movementArea;

	GridMap*					m_gridMap;
};

