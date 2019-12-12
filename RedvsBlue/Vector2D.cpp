#include "Vector2D.h"



Vector2D Vector2D::operator += (const Vector2D &other)
{
	x += other.x;
	y += other.y;
	return *this;
}