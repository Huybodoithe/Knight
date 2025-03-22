#pragma once
#include "GameState.h"
#include <iostream>
#include "Button.h"

using namespace std;

class PauseState :public GameState
{
public:
	virtual bool Enter();
	virtual bool Exit();

	virtual void Update(float dt);
	virtual void Render();

private:
	Button* m_ContinueButton;
	Button* m_QuitButton;
};