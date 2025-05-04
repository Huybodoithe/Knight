#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "string"

using namespace std;

class TextManager
{
public:
	static TextManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextManager(); }
	void Init(const string& fontPath);
	void Render();
	void UpdateKillsCount(int newCount);
	void Clean();

private:
	TextManager();
	
	static TextManager* s_Instance;

	TTF_Font* m_Font;

	SDL_Texture* m_QuestTexture;
	SDL_Texture* m_KillsCount;

	SDL_Rect m_QuestRect;
	SDL_Rect m_KillsRect;
};
