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

Vector2D Rigidbody::GetAcceleration()
{
	return m_Acceleration;
}

void Rigidbody::Update(float dt)
{
	m_Acceleration.X = m_Force.X / m_Mass;
	m_Acceleration.Y = m_Gravity + m_Force.Y / m_Mass;
	m_Velocity = m_Acceleration ;
	m_Position = m_Velocity ;
}
