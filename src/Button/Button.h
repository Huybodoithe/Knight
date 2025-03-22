#pragma once
#include <iostream>
#include "SDL.h"

using namespace std;

class Button
{
public:
	Button(string textureID_default, string textureID_hover, int x, int y, int width, int height);
	void Update();
	void Render();
	bool IsClicked();

private:
	string m_TextureID_Default;
	string m_TextureID_Hover;
	int X, Y;
	int m_Width;
	int m_Height;

	//SDL_Rect m_DestRect;

	bool m_IsHovered;
};