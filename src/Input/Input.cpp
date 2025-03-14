#include "Input.h"
#include "Game.h"
Input* Input::s_Instance = nullptr;

Input::Input()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::Listen()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		Game::GetInstance()->Quit();
		break;
	case SDL_KEYDOWN:
		KeyDown();
		break;
	case SDL_KEYUP:
		KeyUp();
		break;
	default:
		break;
	}
}

bool Input::GetKeyDown(SDL_Scancode key)
{
	if (m_KeyStates[key] == 1) return true;
	else return false;
}

int Input::GetAxisKey(Axis axis)
{
	switch (axis)
	{
	case HORIZONTAL:
		if (GetKeyDown(SDL_SCANCODE_D) || GetKeyDown(SDL_SCANCODE_RIGHT))
		{
			return 1;
		}
		if (GetKeyDown(SDL_SCANCODE_A) || GetKeyDown(SDL_SCANCODE_LEFT))
		{
			return -1;
		}
		break;
	case VERTICAL:
		if (GetKeyDown(SDL_SCANCODE_W) || GetKeyDown(SDL_SCANCODE_UP))
		{
			return 1;
		}
		if (GetKeyDown(SDL_SCANCODE_S) || GetKeyDown(SDL_SCANCODE_DOWN))
		{
			return -1;
		}
		break;
	default:
		return 0;
		break;
	}
}



void Input::KeyUp()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}
