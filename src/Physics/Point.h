#pragma once


class Point
{
public:
	float X, Y;

	Point(float x = 0, float y = 0) : X(x), Y(y) {}

	inline Point operator+(const Point& p2) const
	{
		return Point(X + p2.X, Y + p2.Y);
	}
	
	inline Point& operator+=( const Point& p2)
	{
		X += p2.X;
		Y += p2.Y;
		return *this;
	}

	inline Point operator-(const Point& p2) const
	{
		return Point(X - p2.X, Y - p2.Y);
	}

	inline Point& operator-=(const Point& p2)
	{
		X -= p2.X;
		Y -= p2.Y;
		return *this;
	}

	inline Point operator*(const float scalar) const
	{
		return Point(X * scalar, Y * scalar);
	}
};
