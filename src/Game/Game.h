#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "MapParser.h"
#include "GameObjet.h"
#include "GameState.h"
#include "GameStateMachine.h"
#include "Input.h"
#include "SDL_ttf.h"

using namespace std;


#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Game
{
public:
	Game() {}
	static Game* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Game(); }
	

	bool Init();

	void Update();
	void Events();
	void Render();

	void Clean();
	void Quit();

	/*void PopState();
	void PushState(GameState* current);
	void ChangeState(GameState* target);*/

	bool isRunning() { return m_IsRunning; }
	inline SDL_Renderer* GetRenderer() { return m_Renderer; }
	inline GameMap* GetMap() { return m_Map; }
	inline vector<GameObject*> GetGameObjects() { return m_GameObjects; }
	inline SDL_Rect GetTreasure() { return m_Treasure; }

	inline bool isWon() { return m_IsWon; }
	inline void SetVictory() { m_IsWon = true; }

	inline int GetKillCount() { return m_KillCount; }
	inline void ChangeKillCount() { m_KillCount++; }

	void RemoveGameObject(GameObject* obj);
private:

	static Game* s_Instance;

	bool m_IsRunning;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	GameMap* m_Map;

	vector<GameObject*> m_GameObjects;

	SDL_Rect m_Treasure;

	bool m_IsWon;

	int m_KillCount;
};