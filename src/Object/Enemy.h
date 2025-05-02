#pragma once
#include "GameObjet.h"
#include "Collider.h"
#include "SDL.h"
#include "SeqAnimation.h"
#include "Rigidbody.h"

#define ENEMY_HURT_TIME 0.6f
#define ENEMY_DIE_TIME 0.6f

#define MAXHP 80
#define ENEMY_ATTACK_COOLDOWN_TIME 2.0f

#define ENEMY_ATTACK_TIME 0.5f
#define ENEMY_ATTACK_DAMAGE 10

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
private:
	Collider* m_Collider;
	Rigidbody* m_Rigidbody;
	SeqAnimation* m_Animation;
	Vector2D m_LastSafePosition;

	bool m_IsHurting;
	float m_HurtTime;

	bool m_IsDying;
	float m_DieTime;

	int m_Hp;

	float m_Cooldown;
	bool m_IsAttacking;
	float m_AttakTime;

	SDL_Rect m_VisionBox;
};