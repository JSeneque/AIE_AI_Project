#pragma once
class Vector2D
{
public:
	union {
		struct {
			float x, y;
		};

		float data[2];
	};

	Vector2D Vector2D::operator += (const Vector2D &other);
};

