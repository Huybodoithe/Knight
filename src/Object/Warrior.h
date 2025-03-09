#pragma once
#include "GameObjet.h"
#include "Animation.h"
#include "Rigidbody.h"

class Warrior : public GameObject
{
public:
	Warrior(Properties* props);
	virtual void Update(float dt);
	virtual void Render();
	virtual void Clean();
private:
	Animation* m_Animation;
	Rigidbody* m_Rigidbody;
};