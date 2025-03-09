#include "Game.h"
#include "Timer.h"
int main(int agrc, char* args[])
{
	if (Game::GetInstance()->Init())
	{
		while (Game::GetInstance()->isRunning())
		{
			Game::GetInstance()->Events();
			Game::GetInstance()->Update();
			Game::GetInstance()->Render();
			Timer::GetInstance()->Tick();
		}
	}

	Game::GetInstance()->Clean();
	return 0;
}