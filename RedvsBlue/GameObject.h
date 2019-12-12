#pragma once
#include "Vector2D.h"

namespace aie{
	class Renderer2D;
}

class GameObject
{
public:
	GameObject();
	~GameObject();

	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer);

private:
	Vector2D		m_position;

};

