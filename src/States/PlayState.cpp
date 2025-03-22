#include "PlayState.h"
#include "Game.h"
#include "Camera.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameOverState.h"

bool PlayState::Enter()
{
	m_PauseButton = new Button("PauseButtonDefault", "PauseButtonHover", 30, 30, 32, 32);

    cout << "Enter PlayState" << endl;
	return true;
}

bool PlayState::Exit()
{
	delete m_PauseButton;

    cout << "Exit PlayState" << endl;
	return true;
}

void PlayState::Update(float dt)
{
	m_PauseButton->Update();
	Game::GetInstance()->GetMap()->Update();

	for (int i = 0; i < Game::GetInstance()->GetGameObjects().size(); i++)
	{
		Game::GetInstance()->GetGameObjects()[i]->Update(dt);
	}

	Camera::GetInstance()->Update(dt);

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_M) || m_PauseButton->IsClicked())
	{
		GameStateMachine::GetInstance()->ChangeState(new PauseState());
	}

	if (Game::GetInstance()->GetGameObjects()[0]->IsDead())
	{
		GameStateMachine::GetInstance()->ChangeState(new GameOverState());
	}
}

void PlayState::Render()
{
	
	Game::GetInstance()->GetMap()->Render();

	for (int i = 0; i < Game::GetInstance()->GetGameObjects().size(); i++)
	{
		Game::GetInstance()->GetGameObjects()[i]->Draw();
	}
	m_PauseButton->Render();
}
