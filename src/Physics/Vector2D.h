#pragma once


class Vector2D
{
public:
	Vector2D(float x = 0, float y = 0) : X(x), Y(y) {}

	Vector2D operator+(Vector2D& v2) const
	{
		return Vector2D(X + v2.X, Y + v2.Y);
	}

	Vector2D operator-(Vector2D& v2) const
	{
		return Vector2D(X - v2.X, Y - v2.Y);
	}

	Vector2D operator*(const float scalar) const
	{
		return Vector2D(X * scalar, Y * scalar);
	}

public:
	float X, Y;
};