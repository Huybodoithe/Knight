#pragma once
#include "GameState.h"
#include <vector>

using namespace std;

class GameStateMachine
{
public:
	static inline GameStateMachine* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new GameStateMachine; }
	void PushState(GameState* state);
	void PopState();
	void ChangeState(GameState* state);
	void Update(float dt);
	void Render();

private:
	static GameStateMachine* s_Instance;

	vector<GameState*> m_GameStates;
};