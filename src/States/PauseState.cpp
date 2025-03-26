#include "PauseState.h"
#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"

bool PauseState::Enter()
{
	m_ContinueButton = new Button("ContinueButtonDefault", "ContinueButtonHover", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 -30, 96, 32);
	m_QuitButton = new Button("QuitButtonDefault", "QuitButtonHover", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, 96, 32);

	cout << "Enter PauseState" << endl;
	return true;
}

bool PauseState::Exit()
{
	delete m_ContinueButton;
	delete m_QuitButton;

	cout << "Exit PauseState" << endl;
	return true;
}

void PauseState::Update(float dt)
{
	m_ContinueButton->Update();
	m_QuitButton->Update();
	if (m_ContinueButton->IsClicked())
	{
		GameStateMachine::GetInstance()->ChangeState(new PlayState());
	}
	else if (m_QuitButton->IsClicked())
	{
		Game::GetInstance()->Quit();
	}
}

void PauseState::Render()
{
	TextureManager::GetInstance()->DrawButton("Panel", SCREEN_WIDTH / 2-64, (SCREEN_HEIGHT / 2)-96, 128, 192);
	m_ContinueButton->Render();
	m_QuitButton->Render();
}
