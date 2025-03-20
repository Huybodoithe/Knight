#pragma once
#include "SDL.h"
#include "Game.h"
#include "Camera.h"
//componet box collider
class Collider
{
public:
	inline SDL_Rect Get() { return m_Box; }
	inline void SetBuffer(int x, int y, int width, int height) { m_Buffer = { x,y,width,height }; }

	void Set(int x, int y, int width, int height)
	{
		m_Box = {
			x - m_Buffer.x,
			y - m_Buffer.y,
			width - m_Buffer.w,
			height - m_Buffer.h
		};
	}

	void DrawBox()
	{
		Vector2D cam = Camera::GetInstance()->GetPosition();
		SDL_Rect box = m_Box;
		box.x -= cam.X;
		box.y -= cam.Y;
		SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 255, 255);
		SDL_RenderDrawRect(Game::GetInstance()->GetRenderer(), &box);
	}
private:

	SDL_Rect m_Box;
	SDL_Rect m_Buffer; //giam kich thuoc m_Box
};