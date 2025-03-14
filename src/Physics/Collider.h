#pragma once
#include "SDL.h"

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
private:

	SDL_Rect m_Box;
	SDL_Rect m_Buffer; //giam kich thuoc m_Box
};