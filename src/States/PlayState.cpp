#include "PlayState.h"
#include "Game.h"
#include "Camera.h"
#include "MenuState.h"
#include "PauseState.h"

bool PlayState::Enter()
{
    cout << "Enter PlayState" << endl;
	return true;
}

bool PlayState::Exit()
{
    cout << "Exit PlayState" << endl;
	return true;
}

void PlayState::Update(float dt)
{
	Game::GetInstance()->GetMap()->Update();

	for (int i = 0; i < Game::GetInstance()->GetGameObjects().size(); i++)
	{
		Game::GetInstance()->GetGameObjects()[i]->Update(dt);
	}

	Camera::GetInstance()->Update(dt);

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_M))
	{
		GameStateMachine::GetInstance()->ChangeState(new PauseState());
	}
}

void PlayState::Render()
{
	Game::GetInstance()->GetMap()->Render();

	for (int i = 0; i < Game::GetInstance()->GetGameObjects().size(); i++)
	{
		Game::GetInstance()->GetGameObjects()[i]->Draw();
	}
}
