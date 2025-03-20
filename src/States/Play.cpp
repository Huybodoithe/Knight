#include "Play.h"

Play::Play()
{
}

void Play::Events()
{
}

bool Play::Init()
{
	m_EditMode = false;
	m_Ctxt = Game::GetInstance()->GetRenderer();

	TextureManager::GetInstance()->ParseTextures("assets/textures.tml");
	m_LevelMap = MapParser::GetInstance()->Load("assets/maps/map.tmx");
	TileLayer* collisionLayer = (TileLayer*)Game::GetInstance()->GetMap()->GetMapLayers().front();

	int tilesize = collisionLayer->GetTileSize();
	//int width = collisionLayer->GetWidth()*tilesize;
	//int height = collisionLayer->GetHeight()*tilesize;

	return true;
}

bool Play::Exit()
{
	return false;
}

void Play::Update()
{
}

void Play::Render()
{
}

void Play::OpenMenu()
{
}

void Play::PauseGame()
{
}
