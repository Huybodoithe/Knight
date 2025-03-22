#pragma once



class GameState
{
public:
	virtual bool Enter() = 0;
	virtual bool Exit() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

//protected:
//	SDL_Renderer* m_Ctxt;
};