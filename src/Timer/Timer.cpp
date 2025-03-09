#include "Timer.h"
#include "SDL.h"

Timer* Timer::s_Instance = nullptr;
void Timer::Tick()
{
	float curentTime = SDL_GetTicks();
	m_DeltaTime = (curentTime - m_LastTime) * (FPS/1000.0f);
	if (m_DeltaTime > DELTATIME) m_DeltaTime = DELTATIME;
	m_LastTime = curentTime;
}

float Timer::GetDeltaTime()
{
	return m_DeltaTime;
}
