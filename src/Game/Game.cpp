#include "Game.h"
#include "TextureManager.h"
#include "Warrior.h"
#include "Timer.h"
#include "Camera.h"
#include "Enemy.h"
#include "ObjectFactory.h"
#include "PlayState.h"
#include "MenuState.h"
#include "SoundManager.h"


Game* Game::s_Instance = nullptr;

bool Game::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
	{
		cout << "Failed to initialize SDL : " << SDL_GetError() << endl;
		return false;
	}

	m_Window = SDL_CreateWindow("GOTY", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	if (m_Window == NULL)
	{
		cout << "Faile to create window: " << SDL_GetError() << endl;
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
	if (m_Renderer == NULL)
	{
		cout << "Failed to create renderer: " << SDL_GetError() << endl;
		return false;
	}

	
	if (!MapParser::GetInstance()->Load("assets/maps/mapBodoi.tmx"))
	{
		cout << "Failed to load map" << endl;
	}
	m_Map = MapParser::GetInstance()->GetMap("MAP");

	TextureManager::GetInstance()->ParseTextures("assets/textures.tml");
	SoundManager::GetInstance()->ParseSounds("assets/sounds.tml");


	Properties* props = new Properties("IdleKnight", 50, 450, 120, 80);
	GameObject* Knight = ObjectFactory::GetInstance()->CreateObject("PLAYER", props);

	props = new Properties("SlimeIdle", 300, 100, 32, 25);
	GameObject* Slime1 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 400, 100, 32, 25);
	GameObject* Slime2 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 700, 100, 32, 25);
	GameObject* Slime3 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 1000, 100, 32, 25);
	GameObject* Slime4 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 1200, 100, 32, 25);
	GameObject* Slime5 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);

	m_GameObjects.push_back(Knight);
	m_GameObjects.push_back(Slime1);
	m_GameObjects.push_back(Slime2);
	m_GameObjects.push_back(Slime3);
	m_GameObjects.push_back(Slime4);
	m_GameObjects.push_back(Slime5);

	Camera::GetInstance()->SetTarget(Knight->GetOrigin());

	m_IsRunning = true;

	GameStateMachine::GetInstance()->PushState(new MenuState());

	return true;
}

void Game::Update()
{
	float dt = Timer::GetInstance()->GetDeltaTime();
	
	GameStateMachine::GetInstance()->Update(dt);

}

void Game::Events()
{
	Input::GetInstance()->Listen();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_Renderer);

	GameStateMachine::GetInstance()->Render();
	//TextureManager::GetInstance()->Draw("dragon", 0, 0, 1956, 2801,0.5,0.5);

	/*m_Map->Render();
	
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->Draw();
	}*/
	SDL_RenderPresent(m_Renderer);
}

void Game::RemoveGameObject(GameObject* obj)
{
	auto it = std::find(m_GameObjects.begin(), m_GameObjects.end(), obj);
	if (it != m_GameObjects.end())
	{
		delete* it; // Giải phóng bộ nhớ
		m_GameObjects.erase(it); // Xóa khỏi danh sách
	}
}

void Game::Clean()
{
	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = NULL;

	SDL_DestroyWindow(m_Window);
	m_Window = NULL;
	
	SDL_Quit();
	IMG_Quit();
}

void Game::Quit()
{
	m_IsRunning = false;
}


