#pragma once
#include "GameObjet.h"
#include "Collider.h"
#include "SDL.h"
#include "SeqAnimation.h"
#include "Rigidbody.h"

#define HURTTIME 0.6f
#define DIETIME 0.6f

#define MAXHP 80

class Enemy : public GameObject
{
public:
	Enemy(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

	inline Collider* GetCollider() { return m_Collider; }
	
	void SetHurt();
	void TakeDamage(int damage);
	void Die();
	bool IsDead() { return m_IsDead; }
private:
	Collider* m_Collider;
	Rigidbody* m_Rigidbody;
	SeqAnimation* m_Animation;
	Vector2D m_LastSafePosition;

	bool m_IsHurt;
	float m_HurtTime;

	bool m_IsDying;
	bool m_IsDead;
	float m_DieTime;


	int m_Hp;


};