#pragma once
#include <iostream>
#include "TextureManager.h"
#include "Transform.h"

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
	}

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;
protected:
	Transform* m_Transform;

	string m_TextureID;
	int m_Width, m_Height;
	SDL_RendererFlip m_Flip;

	string m_Name;
};
