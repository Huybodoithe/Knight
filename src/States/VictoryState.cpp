#include "VictoryState.h"
#include "Game.h"

bool VictoryState::Enter()
{
	m_QuitButton = new Button("QuitButtonDefault", "QuitButtonHover", SCREEN_WIDTH / 2-9, SCREEN_HEIGHT / 2+50, 96, 32);
	cout << "Enter VictoryState" << endl;
	return true;
}

bool VictoryState::Exit()
{
	delete m_QuitButton;

	cout << "Exit VictoryState" << endl;
	return true;
}

void VictoryState::Update(float dt)
{
	m_QuitButton->Update();

	if (m_QuitButton->IsClicked())
	{
		Game::GetInstance()->Quit();
	}
}

void VictoryState::Render()
{
	TextureManager::GetInstance()->DrawBackground("VictoryBackground", 0, 0, 960, 640, 1);
	//TextureManager::GetInstance()->Draw("Panel", 0, 0, 128, 192, 1, 1);

	//TextureManager::GetInstance()->DrawButton("Panel", SCREEN_WIDTH / 2 - 64, SCREEN_HEIGHT / 2 - 96, 128, 192);
	m_QuitButton->Render();
}
