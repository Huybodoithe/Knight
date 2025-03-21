#include "Enemy.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include <iostream>
#include "ObjectFactory.h"
#include "Game.h"

static Registrar<Enemy> registrar("ENEMY");

Enemy::Enemy(Properties* props) : GameObject(props)
{
	m_Hp = MAXHP;

	m_IsHurt = false;
	m_HurtTime = HURTTIME;
	m_IsDying = false;
	m_DieTime = DIETIME;
	m_IsDead = false;

	m_Rigidbody = new Rigidbody();
	m_Rigidbody->SetGravity(2.0f);

	m_Collider = new Collider();

	m_Animation = new SeqAnimation(false);
	m_Animation->Parse("assets/animations.tml");
	m_Animation->SetCurrentSeq("SlimeIdle");
}

void Enemy::Draw()
{
	m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 1, 1, m_Flip);

	m_Collider->DrawBox();

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect hpBar = { int(m_Transform->X) - cam.X, int(m_Transform->Y) - 10-cam.Y, m_Hp/2, 5 };
	SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Game::GetInstance()->GetRenderer(), &hpBar);
}

void Enemy::Update(float dt)
{
	m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	//update x axis
	m_Rigidbody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->TransformAddX(m_Rigidbody->GetPosition().X);
	m_Collider->Set(m_Transform->X, m_Transform->Y, 32, 25);
	if (CollisonHandler::GetInstance()->MapCollision(m_Collider->Get()))
	{
		m_Transform->X = m_LastSafePosition.X;
	}

	//update y axis
	m_Rigidbody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->TransformAddY(m_Rigidbody->GetPosition().Y);
	m_Collider->Set(m_Transform->X, m_Transform->Y, 32, 25);
	if (CollisonHandler::GetInstance()->MapCollision(m_Collider->Get()))
	{
		m_Transform->Y = m_LastSafePosition.Y;
	}

	//hurt
	if (m_IsHurt)
	{
		m_HurtTime -= dt;
		if (m_HurtTime <= 0)
		{
			m_IsHurt = false;
			m_Animation->SetCurrentSeq("SlimeIdle");
		}
	}

	//die

	if (!m_IsDying && m_Hp <= 0) Die();
	
	if (m_IsDying)
	{
		m_DieTime -= dt;
		if (m_DieTime <= 0)
		{
			m_IsDying = false;
			m_IsDead = true;
		}
	}

	if (m_IsDead)
	{
		Game::GetInstance()->RemoveGameObject(this);
		return;
	}

	m_Animation->Update(dt);

	if (m_Animation->IsEnded())
	{
		m_Animation->SetRepeat(true);
		m_Animation->SetCurrentSeq("SlimeIdle");
	}

	
	
}

void Enemy::SetHurt()
{
	m_IsHurt = true;
	m_HurtTime = HURTTIME;
	m_Animation->SetCurrentSeq("SlimeHurt");
}

void Enemy::TakeDamage(int damage)
{
	m_Hp -= damage;
}

void Enemy::Die()
{
	m_Animation->SetCurrentSeq("SlimeDie");
	m_IsDying = true;
}

void Enemy::Clean()
{
}


