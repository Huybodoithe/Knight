#include "GameStateMachine.h"

GameStateMachine* GameStateMachine::s_Instance = nullptr;

void GameStateMachine::PushState(GameState* state)
{
	m_GameStates.push_back(state);
	state->Enter();
}

void GameStateMachine::PopState()
{
	if (!m_GameStates.empty())
	{
		m_GameStates.back()->Exit();
		delete m_GameStates.back();
		m_GameStates.pop_back();
	}
}

void GameStateMachine::ChangeState(GameState* state)
{
	PopState();
	PushState(state);
}

void GameStateMachine::Update(float dt)
{
	if (!m_GameStates.empty()) m_GameStates.back()->Update(dt);
}

void GameStateMachine::Render()
{
	if (!m_GameStates.empty()) m_GameStates.back()->Render();
}
