#pragma once
#include "GameObjet.h"
#include "Collider.h"
#include "SDL.h"
#include "SeqAnimation.h"
#include "Rigidbody.h"

class Enemy : public GameObject
{
public:
	Enemy(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

private:
	Collider* m_Collider;
	Rigidbody* m_Rigidbody;
	SeqAnimation* m_Animation;
	Vector2D m_LastSafePosition;

};