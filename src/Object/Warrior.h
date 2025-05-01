#pragma once
#include "GameObjet.h"
#include "SpriteAnimation.h"
#include "Rigidbody.h"
#include "Point.h"
#include "Collider.h"
#include "CollisionHandler.h"
#include "GameStateMachine.h"

#define JUMPTIME 0.5f
#define JUMPFORCE 10.0f

#define RUN_FORCE 5.0f
#define WARRIOR_ATTACK_TIME 0.32f

#define WARROR_ATTACK_COOLDOWN_TIME 0.6f
#define WARRIOR_ATTACK_DAMAGE 20

#define WARRIOR_MAX_HP 30

#define WARRIOR_HURT_TIME 0.15f
class Warrior : public GameObject
{
public:
	Warrior(Properties* props);
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Clean();

	Collider* GetCollider() { return m_Collider; }

	void SetHurt();
	void TakeDamage(int damage);
	
private:
	void AnimationState();

private:
	int m_Hp;
	

	SpriteAnimation* m_SpriteAnimation;
	Rigidbody* m_Rigidbody;
	
	bool m_IsRunning;
	bool m_IsJumping;
	bool m_IsFalling;
	bool m_IsGrounded;
	bool m_IsAttacking;
	bool m_IsCrouching;
	bool m_IsHurting;


	float m_JumpTime;
	float m_JumpForce;
	float m_AttackTime;
	float m_Cooldown;
	float m_HurtTime;

	Collider* m_Collider;
	Vector2D m_LastSafePosition;

	string m_LastAnimID;
	string m_NewAnimID;


	SDL_Rect m_AttakBox;

	Collider* m_FootCollider;

};