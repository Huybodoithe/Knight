#include "Button.h"
#include "TextureManager.h"
#include "Input.h"

Button::Button(string textureID_default, string textureID_hover, int x, int y, int width, int height)
	:m_TextureID_Default(textureID_default), m_TextureID_Hover(textureID_hover), X(x),Y(y),m_Width(width), m_Height(height)
{
	//m_DestRect = { X,Y,m_Width,m_Height };
	X -= m_Width / 2;
	Y -= m_Height / 2;
}

void Button::Update()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	m_IsHovered = ((mouseX > X && mouseX < X + m_Width) && (mouseY > Y && mouseY < Y + m_Height));
}

void Button::Render()
{
	if (!m_IsHovered) TextureManager::GetInstance()->DrawButton(m_TextureID_Default, X, Y, m_Width, m_Height);
	else TextureManager::GetInstance()->DrawButton(m_TextureID_Hover, X, Y, m_Width, m_Height);
}

bool Button::IsClicked()
{
	return (m_IsHovered && Input::GetInstance()->IsMouseButtonPressed(RIGHT_MOUSE));
}
