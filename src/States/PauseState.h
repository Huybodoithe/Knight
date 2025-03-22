#pragma once
#include "GameState.h"
#include <iostream>

using namespace std;

class PauseState :public GameState
{
public:
	virtual bool Enter();
	virtual bool Exit();

	virtual void Update(float dt);
	virtual void Render();
};