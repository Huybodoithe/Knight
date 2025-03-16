#pragma once
#include <string>
#include "SDL.h"
#include "TextureManager.h"
using namespace std;

//class Animation
//{
//public:
//	Animation() {}
//
//	void Update();
//	void Render(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip);
//	void SetProps(string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
//
//private:
//	string m_TextureID;
//	int m_SpriteRow, m_SpriteFrame;
//	int m_FrameCount, m_AnimSpeed;
//};

class Animation
{
public:
	Animation(bool repeat = true) :m_Repeat(repeat) { m_IsEnded = false; }

	virtual void Update(float dt) = 0;
	inline bool IsEnded() { return m_IsEnded; }

protected:

	bool m_Repeat;
	bool m_IsEnded;
	int m_CurrentFrame;
};