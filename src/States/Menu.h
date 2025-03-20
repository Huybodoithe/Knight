#pragma once
#include "SDL.h"
#include "GameState.h"
#include <iostream>

using namespace std;

class Menu : public GameState
{
public:
	Menu();
	virtual bool Init();
	virtual bool Exit();

	virtual void Update();
	virtual void Render();

private:
	static void StartGame();
	static void Settings();
	static void Editor();
	static void Quit();

};