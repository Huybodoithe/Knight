#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat)
{
}

void SpriteAnimation::Update(float dt)
{
	m_CurrentFrame = ((SDL_GetTicks()-m_StartTime) / m_Speed) % m_FrameCount;
}

void SpriteAnimation::Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale, float yScale, SDL_RendererFlip flip)
{
	TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_CurrentFrame, flip);
}

void SpriteAnimation::SetProps(string textureID, int spriteRow, int frameCount, int speed)
{
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
	m_Speed = speed;

	m_StartTime = SDL_GetTicks();
}
