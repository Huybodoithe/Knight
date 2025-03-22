#include "PauseState.h"
#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"

bool PauseState::Enter()
{
	cout << "Enter PauseState" << endl;
	return true;
}

bool PauseState::Exit()
{
	cout << "Exit PauseState" << endl;
	return true;
}

void PauseState::Update(float dt)
{
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN))
	{
		GameStateMachine::GetInstance()->ChangeState(new PlayState());
	}
}

void PauseState::Render()
{
}
