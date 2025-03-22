#pragma once
#include "SDL.h"

enum Axis {HORIZONTAL, VERTICAL};

enum MouseButton {LEFT_MOUSE, RIGHT_MOUSE, MIDDLE_MOUSE};

class Input
{
public:
	static Input* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input(); }

	void Listen();
	bool GetKeyDown(SDL_Scancode key);
	
	int GetAxisKey(Axis axis);

	bool IsMouseButtonDown(MouseButton button);
	bool IsMouseButtonPressed(MouseButton button);

private:
	Input();
	static Input* s_Instance;

	void KeyUp();
	void KeyDown();

	const Uint8* m_KeyStates;

	bool m_MouseButtons[3] = { false,false,false };
	bool m_MousePressed[3] = { false,false,false };
};
