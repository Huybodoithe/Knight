#include "Timer.h"
#include "SDL.h"

Timer* Timer::s_Instance = nullptr;

void Timer::Tick()
{
	Uint32 currentTime = SDL_GetTicks();
	m_DeltaTime = (currentTime - m_LastTime) * (1.0f / 1000.0f);
	if (m_DeltaTime > DELTATIME)
	{
		m_DeltaTime = DELTATIME;
	}
	m_LastTime = currentTime;

	Uint32 frameTime = SDL_GetTicks() - currentTime;
	if (frameTime < (1000.0f / FPS)) // 60 FPS ~ 16.67ms mỗi frame
	{
		SDL_Delay((1000.0f / FPS) - frameTime);
	}
}

float Timer::GetDeltaTime()
{
	return m_DeltaTime; 
}
