#include "Menu.h"
#include "Game.h"

Menu::Menu()
{
}

bool Menu::Init()
{
	m_Ctxt = Game::GetInstance()->GetRenderer();
	cout << "Menu initialized!" << endl;
	return true;
}

bool Menu::Exit()
{
	cout << "Exit menu~" << endl;
	return true;
}

void Menu::Update()
{
}

void Menu::Render()
{
	SDL_SetRenderDrawColor(m_Ctxt, 16, 45, 70, 255);
	SDL_RenderClear(m_Ctxt);

	SDL_RenderPresent(m_Ctxt);
}

void Menu::StartGame()
{
	cout << "Start Game!" << endl;
}

void Menu::Settings()
{
	cout << "Settings mode" << endl;
}

void Menu::Editor()
{
	cout << "Editor mode" << endl;
}

void Menu::Quit()
{
}
