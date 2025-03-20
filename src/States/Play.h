#pragma once
#include "Game.h"


class Play : public GameState
{
public: 
	Play();
	void Events();

	virtual bool Init();
	virtual bool Exit();

	virtual void Update();
	virtual void Render();

private:
	static void OpenMenu();
	static void PauseGame();

	bool m_EditMode;
	GameMap* m_LevelMap;
	vector<GameObject*> m_GameObjects;
};