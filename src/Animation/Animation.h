#pragma once
#include <string>
#include "SDL.h"
#include "TextureManager.h"
using namespace std;

class Animation
{
public:
	Animation() {}

	void Update();
	void Render(float x, float y, int spriteWidth, int spriteHeight);
	void SetProps(string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	string m_TextureID;
	int m_SpriteRow, m_SpriteFrame;
	int m_FrameCount, m_AnimSpeed;
	SDL_RendererFlip m_Flip;
};