#pragma once
#include "Vector2D.h"


//Component cho biet vi tri Object
class Transform
{ 

public:
	Transform(float x = 0, float y = 0) : X(x), Y(y) {}

	void TransformAddX(float x) { X += x; }
	void TransformAddY(float y) { Y += y; }
	void TransformAdd(Vector2D v)
	{
		X += v.X;
		Y += v.Y;
	}

public:
	float X, Y;
};