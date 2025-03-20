#pragma once
#include "GameObjet.h"
#include "Collider.h"
#include "SDL.h"
#include "SeqAnimation.h"
#include "Rigidbody.h"

#define HURTTIME 0.5f

class Enemy : public GameObject
{
public:
	Enemy(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

	inline Collider* GetCollider() { return m_Collider; }
	
	void SetHurt();

private:
	Collider* m_Collider;
	Rigidbody* m_Rigidbody;
	SeqAnimation* m_Animation;
	Vector2D m_LastSafePosition;

	bool m_IsHurt;
	float m_HurtTime;

};