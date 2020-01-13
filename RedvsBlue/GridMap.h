#pragma once
/*
	The Grid Map class will take care of creating the grid map and methods relating to position of the grids
	as well as returns the screen coordinates
*/
#include <vector>
#include "Graph.h"
#include "Global.h"
#include "Renderer2D.h"


class GridMap
{
public:
	GridMap(int c, int r, int t) : m_columns{ c }, m_rows{ r }, m_tileSize{ t }
	{
		m_grid.clear();
		m_grid.resize(m_columns * m_rows); 
	};

	~GridMap();
	void CreateMap();
	void Print();

public:
	int getGridIndex(int const mouseX, int const mouseY) const;

	void setTileAt(int x, int y, ObjectType tileType);
	int getGridSize();
	ObjectType getGridMapTile(int index);
	void draw(aie::Renderer2D* renderer);
	void drawHover(aie::Renderer2D* renderer, int x, int y);
	void drawGridLine(aie::Renderer2D* renderer);
	void addUnit(Unit unit);
	int getColumn(int const mouseX) const;
	int getRow(int const mouseY) const;
	bool CheckBounds(int const mouseX, int const mouseY) const;

private:
	void drawTiles(aie::Renderer2D* renderer);
	void drawUnits(aie::Renderer2D* renderer);
	int getScreenCoordinateX(int const index) const;
	int getScreenCoordinateY(int const index) const;
	
	

private:
	int							m_columns;
	int							m_rows;
	int							m_tileSize;
	std::vector<ObjectType>		m_grid;
	// this list holds all the units on the board
	std::vector<Unit>			m_units;

};

