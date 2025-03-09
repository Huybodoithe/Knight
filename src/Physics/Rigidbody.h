#pragma once
#include "Vector2D.h"

#define MASS 1.0f
#define GRAVITY 9.8f

#define FORWARD 1.0f
#define BACKWARD -1.0f

class Rigidbody
{
public:
	Rigidbody()
	{
		m_Mass = MASS;
		m_Gravity = GRAVITY;
	}

	void ApplyForce(Vector2D force);
	void ApplyForceX(float X);
	void ApplyForceY(float y);
	void UnSetForce();

	float GetMass();
	Vector2D GetPosition();
	Vector2D GetVelocity();
	Vector2D GetAccelaration();

	void Update(float dt);
private:

	float m_Mass; //khoi luong
	float m_Gravity;//gia toc trai dat

	Vector2D m_Force; //luc tac dung
	Vector2D m_Position;//Vi tri
	Vector2D m_Velocity; //Van toc
	Vector2D m_Accelaration; //gia toc
};