#include "Warrior.h"
#include "Input.h"
#include "Camera.h"
#include "Game.h"

Warrior::Warrior(Properties* props) : GameObject(props)
{
	m_IsRunning = false;
	m_IsJumping = false;
	m_IsFalling = false;
	m_IsGrounded = false;
	m_IsAttacking = false;
	m_IsCrouching = false;

	m_SpriteAnimation = new SpriteAnimation();
	m_Rigidbody = new Rigidbody();
	m_Rigidbody->SetGravity(3.0f);

	m_JumpTime = JUMPTIME;
	m_JumpForce = JUMPFORCE;
	m_AttackTime = ATTACK_TIME;

	m_Collider = new Collider();
	m_Collider->SetBuffer(-40, -40, 100, 40);
}

Point* Warrior::GetOrigin()
{
	return m_Origin;
}


void Warrior::Update(float dt)
{
	m_Rigidbody->UnSetForce();
	m_SpriteAnimation->SetProps(m_TextureID, 0, 10, 80);

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
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K))
	{
		m_Rigidbody->UnSetForce();
		m_IsAttacking = true;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded)
	{
		m_IsJumping = true;
		m_IsGrounded = false;
		m_Rigidbody->ApplyForceY(UPWARD * m_JumpForce);
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
		m_AttackTime = ATTACK_TIME;
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
		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else
	{
		m_IsGrounded = false;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	AnimationState();

	cout << dt << endl;
	m_SpriteAnimation->Update(dt);

	
}

void Warrior::Draw()
{
	m_SpriteAnimation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, 1, 1, m_Flip);

	m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();
	box.x -= cam.X;
	box.y -= cam.Y;
	SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 255, 255);
	SDL_RenderDrawRect(Game::GetInstance()->GetRenderer(), &box);
}

void Warrior::AnimationState()
{
	//idling
	m_SpriteAnimation->SetProps("IdleKnight", 0, 10, 80);

	//running
	if(m_IsRunning) m_SpriteAnimation->SetProps("RunKnight", 0, 10, 80);

	//crouching
	if (m_IsCrouching) m_SpriteAnimation->SetProps("CrouchKnight", 0, 1, 200);

	//jumping
	if (m_IsJumping) m_SpriteAnimation->SetProps("JumpKnight", 0, 3, 200);

	//falling
	if (m_IsFalling) m_SpriteAnimation->SetProps("FallKnight", 0, 3, 350);

	//attacking
	if (m_IsAttacking) m_SpriteAnimation->SetProps("Attack1Knight", 0, 4, 60);
}

void Warrior::Clean()
{
}

