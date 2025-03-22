#pragma once
#include "GameState.h"
#include <iostream>
#include "Button.h"

using namespace std;

class PlayState :public GameState
{
public :
	virtual bool Enter();
	virtual bool Exit();

	virtual void Update(float dt);
	virtual void Render();

private:
	Button* m_PauseButton;
};