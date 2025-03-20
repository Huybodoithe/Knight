#pragma once
#include "GameObjet.h"
#include "SpriteAnimation.h"
#include "Rigidbody.h"
#include "Point.h"
#include "Collider.h"
#include "CollisionHandler.h"

#define JUMPTIME 5.0f
#define JUMPFORCE 10.0f

#define RUN_FORCE 5.0f
#define ATTACK_TIME 0.2f

class Warrior : public GameObject
{
public:
	Warrior(Properties* props);
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Clean();


private:
	void AnimationState();

private:
	SpriteAnimation* m_SpriteAnimation;
	Rigidbody* m_Rigidbody;
	
	bool m_IsRunning;
	bool m_IsJumping;
	bool m_IsFalling;
	bool m_IsGrounded;
	bool m_IsAttacking;
	bool m_IsCrouching;

	float m_JumpTime;
	float m_JumpForce;
	float m_AttackTime;

	Collider* m_Collider;
	Vector2D m_LastSafePosition;

};