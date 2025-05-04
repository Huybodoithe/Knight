#include "Enemy.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include <iostream>
#include "ObjectFactory.h"
#include "Game.h"
#include "Warrior.h"
#include "SoundManager.h"
#include "TextManager.h"


static Registrar<Enemy> registrar("ENEMY");

Enemy::Enemy(Properties* props) : GameObject(props)
{
	m_Hp = MAXHP;

	m_IsHurting = false;
	m_HurtTime = ENEMY_HURT_TIME;
	m_IsDying = false;
	m_DieTime = ENEMY_DIE_TIME;
	m_IsDead = false;
	m_Cooldown = 0;
	m_IsAttacking = false;
	m_AttakTime = ENEMY_ATTACK_TIME;

	m_Rigidbody = new Rigidbody();
	m_Rigidbody->SetGravity(2.0f);

	m_Collider = new Collider();
	m_Collider->SetBuffer(-5, -5, 10, 5);

	m_Animation = new SeqAnimation(false);
	m_Animation->Parse("assets/animations.tml");
	m_Animation->SetCurrentSeq("SlimeIdle");

	m_VisionBox = { int(m_Transform->X)-100, int(m_Transform->Y),100 + 32 + 100,50 + 25 };

}

void Enemy::Draw()
{
	m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 1, 1, m_Flip);

	//m_Collider->DrawBox();

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();
	SDL_Rect hpBar = { box.x - cam.X, box.y - 10 - cam.Y, m_Hp / 2, 5 };
	SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Game::GetInstance()->GetRenderer(), &hpBar);
	//SDL_Rect visionBox = { m_VisionBox.x - cam.X, m_VisionBox.y - cam.Y, m_VisionBox.w,m_VisionBox.h };
	//SDL_RenderDrawRect(Game::GetInstance()->GetRenderer(), &visionBox);

}

void Enemy::Update(float dt)
{
	m_Rigidbody->UnSetForce();
	m_VisionBox = { int(m_Transform->X) - 100, int(m_Transform->Y)-50,100 + 32 + 100,50 + 25 };

	Warrior* warrior = dynamic_cast<Warrior*>(Game::GetInstance()->GetGameObjects()[0]);

	m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	if (CollisonHandler::GetInstance()->CheckCollision(m_VisionBox, warrior->GetCollider()->Get()))
	{
		if (!m_IsAttacking && !m_IsHurting && !m_IsDying)
		{
			if(m_Origin->X < warrior->GetOrigin()->X) m_Rigidbody->ApplyForceX(2.0f);
			else m_Rigidbody->ApplyForceX(-2.0f);
			if (CollisonHandler::GetInstance()->CheckCollision(m_Collider->Get(), warrior->GetCollider()->Get())) m_Rigidbody->UnSetForce();
		}
	}


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
	if (m_IsHurting)
	{
		m_HurtTime -= dt;
		if (m_HurtTime <= 0)
		{
			m_IsHurting = false;
			m_Animation->SetCurrentSeq("SlimeIdle");
		}
	}

	//attack
	
	if (!m_IsDying)
	{
		if (CollisonHandler::GetInstance()->CheckCollision(m_Collider->Get(), warrior->GetCollider()->Get()))
		{
			if (m_Cooldown <= 0)
			{
				m_IsAttacking = true;
				m_Animation->SetCurrentSeq("SlimeAttack");
				m_Cooldown = ENEMY_ATTACK_COOLDOWN_TIME;

				warrior->SetHurt();
				SoundManager::GetInstance()->PlayEffect("hurt");
				warrior->TakeDamage(ENEMY_ATTACK_DAMAGE);
			}
		}
	}
	

	if (m_IsAttacking)
	{
		m_AttakTime -= dt;
		if (m_AttakTime <= 0)
		{
			m_IsAttacking = false;
			m_Animation->SetCurrentSeq("SlimeIdle");
			m_AttakTime = ENEMY_ATTACK_TIME;
		}
	}
	if (m_Cooldown > 0)
	{
		m_Cooldown -= dt;
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
			Game::GetInstance()->ChangeKillCount();
			TextManager::GetInstance()->UpdateKillsCount(Game::GetInstance()->GetKillCount());
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


	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;
	
	if (m_Origin->X < warrior->GetOrigin()->X) m_Flip = SDL_FLIP_HORIZONTAL;
	else m_Flip = SDL_FLIP_NONE;
}

void Enemy::SetHurt()
{
	m_IsHurting = true;
	m_HurtTime = ENEMY_HURT_TIME;
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


