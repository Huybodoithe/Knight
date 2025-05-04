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
#include "TextManager.h"


Game* Game::s_Instance = nullptr;

bool Game::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
	{
		cout << "Failed to initialize SDL : " << SDL_GetError() << endl;
		return false;
	}

	if (TTF_Init() == -1) {
		SDL_Log("Failed to init SDL_ttf: %s", TTF_GetError());
		return -1;
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

	TextManager::GetInstance()->Init("assets/Font/28 Days Later.ttf");
	
	if (!MapParser::GetInstance()->Load("assets/maps/mapBodoi.tmx"))
	{
		cout << "Failed to load map" << endl;
	}
	m_Map = MapParser::GetInstance()->GetMap("MAP");

	TextureManager::GetInstance()->ParseTextures("assets/textures.tml");
	SoundManager::GetInstance()->ParseSounds("assets/sounds.tml");


	Properties* props = new Properties("IdleKnight", 32 * 3, 1280 + 32 * 8, 120, 80);
	GameObject* Knight = ObjectFactory::GetInstance()->CreateObject("PLAYER", props);

	props = new Properties("SlimeIdle", 352, 128, 32, 25);
	GameObject* Slime1 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 320 + 32 * 5, 128, 32, 25);
	GameObject* Slime2 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 640 + 32 * 3, 128, 32, 25);
	GameObject* Slime3 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 960 + 32 * 2, 128, 32, 25);
	GameObject* Slime4 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 960 + 32 * 4, 128, 32, 25);
	GameObject* Slime5 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 960 + 32 * 6, 128, 32, 25);
	GameObject* Slime6 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 1280 , 128, 32, 25);
	GameObject* Slime7 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 32*2, 320+32*5, 32, 25);
	GameObject* Slime8 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 320 + 32 * 8, 320 + 32 * 3, 32, 25);
	GameObject* Slime9 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 640 + 32 * 3, 320 + 32 * 5, 32, 25);
	GameObject* Slime10 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 320, 960 + 32 * 8, 32, 25);
	GameObject* Slime11 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 960 + 32 , 320 + 32 * 5, 32, 25);
	GameObject* Slime12 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 1280, 320, 32, 25);
	GameObject* Slime13 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 1600+32*7, 320 + 32, 32, 25);
	GameObject* Slime14 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 32 * 9, 640 + 32*3, 32, 25);
	GameObject* Slime15 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 640, 640, 32, 25);
	GameObject* Slime16 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 960+32*3, 640 + 32, 32, 25);
	GameObject* Slime17 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 1600+32*6, 640 + 32 * 3, 32, 25);
	GameObject* Slime18 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 1600, 1280 + 32 * 2, 32, 25);
	GameObject* Slime19 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);
	props = new Properties("SlimeIdle", 960 + 32 * 8, 1600 + 32, 32, 25);
	GameObject* Slime20 = ObjectFactory::GetInstance()->CreateObject("ENEMY", props);

	m_GameObjects.push_back(Knight);//player

	//slime
	m_GameObjects.push_back(Slime1);
	m_GameObjects.push_back(Slime2);
	m_GameObjects.push_back(Slime3);
	m_GameObjects.push_back(Slime4);
	m_GameObjects.push_back(Slime5);
	m_GameObjects.push_back(Slime6);
	m_GameObjects.push_back(Slime7);
	m_GameObjects.push_back(Slime8);
	m_GameObjects.push_back(Slime9);
	m_GameObjects.push_back(Slime10);
	m_GameObjects.push_back(Slime11);
	m_GameObjects.push_back(Slime12);
	m_GameObjects.push_back(Slime13);
	m_GameObjects.push_back(Slime14);
	m_GameObjects.push_back(Slime15);
	m_GameObjects.push_back(Slime16);
	m_GameObjects.push_back(Slime17);
	m_GameObjects.push_back(Slime18);
	m_GameObjects.push_back(Slime19);
	m_GameObjects.push_back(Slime20);

	Camera::GetInstance()->SetTarget(Knight->GetOrigin());

	m_IsRunning = true;

	m_Treasure = { 1824,96,32,32 };
	m_IsWon = false;

	m_KillCount = 0;

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
	TTF_Quit();
}

void Game::Quit()
{
	m_IsRunning = false;
}


