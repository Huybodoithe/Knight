#pragma once

const int FPS = 120;
const float DELTATIME = 1.0f;
class Timer
{
public:
	static Timer* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer(); }

	void Tick();
	float GetDeltaTime();

private:
	Timer() {}
	static Timer* s_Instance;
	float m_DeltaTime;
	float m_LastTime;
};