#pragma once
class Grid
{
public:
	Grid();
	Grid(int width, int height);
	~Grid();

	void Initialise();
	void Print();

private:
	int		m_width;
	int		m_height;
	int**	gridArray = new int*[m_height];
};

