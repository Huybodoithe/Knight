#pragma once
#include <iostream>
#include "TextureManager.h"
#include "Transform.h"
#include "Point.h"

using namespace std;

struct Properties
{
	string TextureID;
	int X, Y;
	int Width;
	int Height;
	SDL_RendererFlip Flip;

	Properties(string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		TextureID = textureID;
		Width = width;
		Height = height;
		X = x;
		Y = y;
		Flip = flip;
	}

};

class GameObject
{
public:
	GameObject(Properties* props)
		: m_TextureID(props->TextureID), m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip)
	{
		m_Transform = new Transform(props->X, props->Y);

		float px = m_Transform->X + m_Width / 2;
		float py = m_Transform->Y + m_Height / 2;

		m_Origin = new Point(px, py);
	}

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void Clean() = 0;
protected:
	Transform* m_Transform;

	string m_TextureID;
	int m_Width, m_Height;
	SDL_RendererFlip m_Flip;

	string m_Name;

	Point* m_Origin;
};
