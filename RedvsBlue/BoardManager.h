#pragma once
#include "GameObject.h"
#include <vector>
#include "Renderer2D.h"
#include "Input.h"
#include "Tile.h"
#include "Graph.h"



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
	void BoardSetup();
	void ClearHoverList();

private:
	int							m_columns;
	int							m_rows;
	Count*						m_waterTileCount;
	
	aie::Renderer2D*			m_2dRenderer;
	int							m_tileSize;
	int							m_leftBorder;
	int							m_bottomBorder;

	std::vector<TileType>		m_grid;
	std::vector<bool>			m_hover;
	// this list holds the background tiles
	std::vector<Node>			m_mapData;
	// combined the others lists into a weighted nodes
	std::vector<Node>			m_nodeList;



};

