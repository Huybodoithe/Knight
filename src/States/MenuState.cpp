#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"

bool MenuState::Enter()
{
	m_StartButton = new Button("StartButtonDefault", "StartButtonHover", 200, 300, 64, 32);

	cout << "Enter MenuState" << endl;
	return true;
}

bool MenuState::Exit()
{
	delete m_StartButton;
	cout << "Exit MenuState" << endl;
	return true;
}

void MenuState::Update(float dt)
{
	m_StartButton->Update();
	if (m_StartButton->IsClicked())
	{
		GameStateMachine::GetInstance()->ChangeState(new PlayState());
	}
}

void MenuState::Render()
{
	m_StartButton->Render();
}
