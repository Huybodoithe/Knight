#include "Game.h"
#include "TextureManager.h"
#include "Warrior.h"
#include "Input.h"
#include "Timer.h"
#include "Camera.h"


Game* Game::s_Instance = nullptr;
Warrior* Knight = nullptr;

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
	
	if (!MapParser::GetInstance()->Load())
	{
		cout << "Failed to load map" << endl;
	}
	m_Map = MapParser::GetInstance()->GetMap("MAP");

	/*TextureManager::GetInstance()->Load("dragon", "assets/Dragon Tyrant.png");
	TextureManager::GetInstance()->Load("IdleKnight", "assets/IdleKnight.png");
	TextureManager::GetInstance()->Load("RunKnight", "assets/RunKnight.png");
	TextureManager::GetInstance()->Load("JumpKnight", "assets/JumpKnight.png");
	TextureManager::GetInstance()->Load("FallKnight", "assets/FallKnight.png");
	TextureManager::GetInstance()->Load("Attack1Knight", "assets/Attack1Knight.png");
	TextureManager::GetInstance()->Load("CrouchKnight", "assets/CrouchKnight.png");*/

	TextureManager::GetInstance()->ParseTextures("assets/textures.tml");

	Knight = new Warrior(new Properties("IdleKnight", 50, 100, 120, 80));

	Camera::GetInstance()->SetTarget(Knight->GetOrigin());

	m_IsRunning = true;

	return true;
}

void Game::Update()
{
	float dt = Timer::GetInstance()->GetDeltaTime();
	
	m_Map->Update();
	
	Knight->Update(dt);
	
	Camera::GetInstance()->Update(dt);
}

void Game::Events()
{
	Input::GetInstance()->Listen();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_Renderer);

	TextureManager::GetInstance()->Draw("dragon", 0, 0, 1956, 2801,0.5);

	m_Map->Render();
	
	Knight->Render();
	SDL_RenderPresent(m_Renderer);
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
