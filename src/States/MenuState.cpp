#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"

bool MenuState::Enter()
{
	m_StartButton = new Button("StartButtonDefault", "StartButtonHover", SCREEN_WIDTH/2, SCREEN_HEIGHT/2-30, 96, 32);
	m_QuitButton = new Button("QuitButtonDefault", "QuitButtonHover", SCREEN_WIDTH/2, SCREEN_HEIGHT/2+50, 96, 32);

	cout << "Enter MenuState" << endl;
	return true;
}

bool MenuState::Exit()
{
	delete m_StartButton;
	delete m_QuitButton;

	cout << "Exit MenuState" << endl;
	return true;
}

void MenuState::Update(float dt)
{
	m_StartButton->Update();
	m_QuitButton->Update();
	if (m_StartButton->IsClicked())
	{
		GameStateMachine::GetInstance()->ChangeState(new PlayState());
	}
	else if (m_QuitButton->IsClicked())
	{
		Game::GetInstance()->Quit();
	}
}

void MenuState::Render()
{
	TextureManager::GetInstance()->Draw("Panel", SCREEN_WIDTH/2-64, SCREEN_HEIGHT/2-96, 128, 192, 1, 1);
	m_StartButton->Render();
	m_QuitButton->Render();
}
