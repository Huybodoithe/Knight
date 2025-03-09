#include "Rigidbody.h"

void Rigidbody::ApplyForce(Vector2D force)
{
	m_Force = force;
}

void Rigidbody::ApplyForceX(float x)
{
	m_Force.X = x;
}

void Rigidbody::ApplyForceY(float y)
{
	m_Force.Y = y;
}

void Rigidbody::UnSetForce()
{
	m_Force = Vector2D(0, 0);
}

float Rigidbody::GetMass()
{
	return m_Mass;
}

Vector2D Rigidbody::GetPosition()
{
	return m_Position;
}

Vector2D Rigidbody::GetVelocity()
{
	return m_Velocity;
}

Vector2D Rigidbody::GetAccelaration()
{
	return m_Accelaration;
}

void Rigidbody::Update(float dt)
{
	m_Accelaration.X = m_Force.X / m_Mass;
	m_Accelaration.Y = m_Gravity + m_Force.Y / m_Mass;
	m_Velocity = m_Accelaration * dt;
	m_Position = m_Velocity * dt;
}
