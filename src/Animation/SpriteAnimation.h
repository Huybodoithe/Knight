#pragma once
#include <string>
#include "Animation.h"
#include "SDL.h"

class SpriteAnimation : public Animation
{
public:

	SpriteAnimation(bool repeat = true);

	virtual void Update(float dt);

	void Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SetProps(string textureID, int spriteRow, int frameCount, int speed);

	int GetCurrentFrame() {return m_CurrentFrame;}

	int GetCurrentSpriteRow() { return m_SpriteRow; }
	void SetSpriteRow(int row) { m_SpriteRow = row; }
	void IncreaseSpriteRow() { m_SpriteRow++; }
	void DecreaseSpriteRow() { m_SpriteRow--; }
protected:

	int m_Speed;
	int m_SpriteRow;
	int m_FrameCount;
	string m_TextureID;
};
