#pragma once
#include "SDL.h"
#include "Point.h"
#include "Vector2D.h"
#include <iostream>

using namespace std;

class Camera
{

public:
	static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }
	SDL_Rect GetViewBox();
	Vector2D GetPosition();
	void SetTarget(Point* target);

	void Update(float dt);


private:
	static Camera* s_Instance;
	Point* m_Target;
	SDL_Rect m_ViewBox;
	Vector2D m_Position;
};