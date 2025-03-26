#include "Camera.h"
#include "Game.h"

Camera* Camera::s_Instance = nullptr;

SDL_Rect Camera::GetViewBox()
{
	return m_ViewBox;
}

Vector2D Camera::GetPosition()
{
	return m_Position;
}

void Camera::SetTarget(Point* target)
{
	m_Target = target;
}

void Camera::Update(float dt)
{
	if (m_Target != nullptr)
	{

		m_ViewBox.x = m_Target->X - SCREEN_WIDTH / 2;
		m_ViewBox.y = m_Target->Y - SCREEN_HEIGHT / 2;
		m_ViewBox.w = SCREEN_WIDTH;
		m_ViewBox.h = SCREEN_HEIGHT;

		if (m_ViewBox.x < 0)
		{
			m_ViewBox.x = 0;
		}
		if (m_ViewBox.x > 2 * SCREEN_WIDTH - m_ViewBox.w)
		{
			m_ViewBox.x = 2 * SCREEN_WIDTH - m_ViewBox.w;
		}
		if (m_ViewBox.y < 0)
		{
			m_ViewBox.y = 0;
		}
		else if (m_ViewBox.y > SCREEN_HEIGHT*3 - m_ViewBox.h)
		{
			m_ViewBox.y = SCREEN_HEIGHT*3 - m_ViewBox.h;
		}

		m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
	}
}
