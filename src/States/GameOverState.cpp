#include "GameOverState.h"
#include "Game.h"

bool GameOverState::Enter()
{
	m_QuitButton = new Button("QuitButtonDefault", "QuitButtonHover", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2-2 , 96, 32);
	cout << "Enter GameOverState" << endl;
	return true;
}

bool GameOverState::Exit()
{
	delete m_QuitButton;

	cout << "Exit GameOverState" << endl;
	return true;
}

void GameOverState::Update(float dt)
{
	m_QuitButton->Update();
	
	if (m_QuitButton->IsClicked())
	{
		Game::GetInstance()->Quit();
	}
}

void GameOverState::Render()
{
	TextureManager::GetInstance()->DrawBackground("GameOverBackground", 0, 0, 960, 640, 1);
	//TextureManager::GetInstance()->DrawButton("Panel", SCREEN_WIDTH / 2 - 64, SCREEN_HEIGHT / 2 - 96, 128, 192);
	m_QuitButton->Render();
}
