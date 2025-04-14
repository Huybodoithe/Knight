#include "Warrior.h"
#include "Input.h"
#include "Camera.h"
#include "Game.h"
#include "ObjectFactory.h"
#include "Enemy.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "SoundManager.h"


static Registrar<Warrior> registrar("PLAYER");

Warrior::Warrior(Properties* props) : GameObject(props)
{
	m_Hp = WARRIOR_MAX_HP;

	m_LastAnimID = "IdleKnight";
	m_NewAnimID = "IdleKnight";

	m_IsRunning = false;
	m_IsJumping = false;
	m_IsFalling = false;
	m_IsGrounded = false;
	m_IsAttacking = false;
	m_IsCrouching = false;
	
	m_SpriteAnimation = new SpriteAnimation();
	m_Rigidbody = new Rigidbody();
	m_Rigidbody->SetGravity(10.0f);
	m_Rigidbody->SetMass(50.0f);

	m_JumpTime = JUMPTIME;
	m_JumpForce = JUMPFORCE;
	m_AttackTime = WARRIOR_ATTACK_TIME;
	m_Cooldown = 0;

	m_Collider = new Collider();
	m_Collider->SetBuffer(-50, -40, 100, 41);

	m_FootCollider = new Collider();
	m_FootCollider->SetBuffer(-50,-70, 100, 66);
}

void Warrior::Update(float dt)
{
	//dead
	cout << dt << endl;
	if (m_Hp <= 0)
	{
		m_IsDead = true;
		return;
	}

	m_Rigidbody->UnSetForce();

	//sang phai
	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking)
	{
		m_Rigidbody->ApplyForceX(RUN_FORCE * FORWARD);
		m_IsRunning = true;
		m_Flip = SDL_FLIP_NONE;
	}

	//sang trai
	else if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking)
	{
		m_Rigidbody->ApplyForceX(RUN_FORCE * BACKWARD);
		m_IsRunning = true;
		m_Flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		m_IsRunning = false;
	}

	//ngoi
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
	{
		m_Rigidbody->UnSetForce();
		m_IsCrouching = true;
	}
	else
	{
		m_IsCrouching = false;
	}

	//attack
	if (Input::GetInstance()->IsMouseButtonPressed(LEFT_MOUSE) && m_Cooldown <= 0)
	{
		m_Rigidbody->UnSetForce();
		m_IsAttacking = true;
		m_Cooldown = WARROR_ATTACK_COOLDOWN_TIME;
	}

	//jump
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded)
	{
		m_IsJumping = true;
		m_IsGrounded = false;
		m_Rigidbody->ApplyForceY(UPWARD * m_JumpForce);
		SoundManager::GetInstance()->PlayEffect("jump");
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping && m_JumpTime > 0)
	{

		m_JumpTime -= dt;
		m_Rigidbody->ApplyForceY(UPWARD * m_JumpForce);
	}
	else
	{
		m_IsJumping = false;
		m_JumpTime = JUMPTIME;
	}

	//falling
	if (m_Rigidbody->GetVelocity().Y > 0 && !m_IsGrounded)
	{
		m_IsFalling = true;
	}
	else
	{
		m_IsFalling = false;
	}

	//attack time
	if (m_IsAttacking && m_AttackTime > 0)
	{
		m_AttackTime -= dt;
	}
	else
	{
		m_IsAttacking = false;
		m_AttackTime = WARRIOR_ATTACK_TIME;
	}
	
	//va cham attack
	if (m_IsAttacking)
	{
		if (m_Flip == SDL_FLIP_NONE)
		{
			m_AttakBox = { m_Collider->Get().x+22 , m_Collider->Get().y, 40, 40};
		}
		else
		{
			m_AttakBox = { m_Collider->Get().x-45, m_Collider->Get().y, 40, 40 };
		}

		

		for (auto obj : Game::GetInstance()->GetGameObjects())
		{
			if (obj == this) continue;

			Enemy* enemy = dynamic_cast<Enemy*>(obj); //lay component enemy

			if (m_Cooldown != WARROR_ATTACK_COOLDOWN_TIME) continue; //cai nay de tan cong thi chi tinh 1 lan damage

			if (CollisonHandler::GetInstance()->CheckCollision(m_AttakBox, enemy->GetCollider()->Get()))
			{
				enemy->SetHurt(); //animation hurt
				enemy->TakeDamage(WARRIOR_ATTACK_DAMAGE); //giam mau enemy
			}
		}
	}

	//cooldown
	if (m_Cooldown > 0)
	{
		m_Cooldown -= dt;
	}

	//hurting
	if (m_IsHurting)
	{
		m_HurtTime -= dt;
		if (m_HurtTime <= 0)
		{
			m_HurtTime = WARRIOR_HURT_TIME;
			m_IsHurting = false;
		}
	}


	//update x axis
	m_Rigidbody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->TransformAddX(m_Rigidbody->GetPosition().X);
	m_Collider->Set(m_Transform->X, m_Transform->Y, 120, 80);
	if (CollisonHandler::GetInstance()->MapCollision(m_Collider->Get()))
	{
		m_Transform->X = m_LastSafePosition.X;
	}
	
	//update y axis
	m_Rigidbody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->TransformAddY(m_Rigidbody->GetPosition().Y);
	m_Collider->Set(m_Transform->X, m_Transform->Y, 120, 80);
	if (CollisonHandler::GetInstance()->MapCollision(m_Collider->Get()))
	{
		//m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else
	{
		//m_IsGrounded = false;
	}

	if (CollisonHandler::GetInstance()->MapCollision(m_FootCollider->Get()))
	{
		m_IsGrounded = true;
		//m_Transform->Y = m_LastSafePosition.Y;
	}
	else
	{
		m_IsGrounded = false;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	
	AnimationState();

	m_SpriteAnimation->Update(dt);
	
}

void Warrior::Draw()
{
	m_SpriteAnimation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, 1, 1, m_Flip);

	//m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	//m_Collider->DrawBox();

	m_FootCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	m_FootCollider->DrawBox();

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();
	SDL_Rect hpBar = { box.x - cam.X, box.y - 10 - cam.Y, m_Hp / 2, 5 };
	SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Game::GetInstance()->GetRenderer(), &hpBar);
	
	if (m_IsAttacking)
	{
		box = m_AttakBox;
		box.x -= cam.X;
		box.y -= cam.Y;
		SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 255, 255);
		SDL_RenderDrawRect(Game::GetInstance()->GetRenderer(), &box);
	}
	
}

void Warrior::AnimationState()
{
	m_NewAnimID = "IdleKnight";
	if (m_IsRunning) m_NewAnimID = "RunKnight";
	if (m_IsCrouching) m_NewAnimID = "CrouchKnight";
	if (m_IsJumping) m_NewAnimID = "JumpKnight";
	if (m_IsAttacking) m_NewAnimID = "Attack1Knight";
	if (m_IsFalling) m_NewAnimID = "FallKnight";
	if (m_IsHurting) m_NewAnimID = "HurtKnight";

	if (m_NewAnimID != m_LastAnimID)
	{
		//idling
		m_SpriteAnimation->SetProps("IdleKnight", 0, 10, 80);

		//running
		if (m_IsRunning) m_SpriteAnimation->SetProps("RunKnight", 0, 10, 80);

		//crouching
		if (m_IsCrouching) m_SpriteAnimation->SetProps("CrouchKnight", 0, 1, 200);

		//jumping
		if (m_IsJumping) m_SpriteAnimation->SetProps("JumpKnight", 0, 3, 200);

		//attacking
		if (m_IsAttacking) m_SpriteAnimation->SetProps("Attack1Knight", 0, 4, 80);

		//falling
		if (m_IsFalling) m_SpriteAnimation->SetProps("FallKnight", 0, 3, 200);

		//hurting
		if (m_IsHurting) {
			m_SpriteAnimation->SetProps("HurtKnight", 0, 1, 100);
		}


		m_LastAnimID = m_NewAnimID;
	}
}


void Warrior::SetHurt()
{
	m_IsHurting = true;
	m_HurtTime = WARRIOR_HURT_TIME;
}

void Warrior::TakeDamage(int damage)
{
	m_Hp -= damage;
}


void Warrior::Clean()
{
}