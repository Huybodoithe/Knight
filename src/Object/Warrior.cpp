#include "Warrior.h"
#include "Input.h"

Warrior::Warrior(Properties* props) : GameObject(props)
{
	m_Animation = new Animation();
	m_Rigidbody = new Rigidbody();
}

void Warrior::Update(float dt)
{
	m_Rigidbody->UnSetForce();
	m_Animation->SetProps(m_TextureID, 0, 10, 80);

	//sang trai
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
	{
		m_Rigidbody->ApplyForceX(10 * BACKWARD);
		m_Animation->SetProps("RunKnight", 0, 10, 80, SDL_FLIP_HORIZONTAL);
	}

	//sang phai
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
	{
		m_Rigidbody->ApplyForceX(10 * FORWARD);
		m_Animation->SetProps("RunKnight", 0, 10, 80);
	}

	m_Rigidbody->Update(dt);
	
	m_Transform->TransformAddX(m_Rigidbody->GetPosition().X);
	//m_Transform->TransformAddY(m_Rigidbody->GetPosition().Y);



	m_Animation->Update();

}

void Warrior::Render()
{
	m_Animation->Render(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Clean()
{
}
