#include "CollisionHandler.h"
#include "Game.h"

CollisonHandler* CollisonHandler::s_Instance = nullptr;

CollisonHandler::CollisonHandler()
{
	m_CollisionLayer = (TileLayer*)Game::GetInstance()->GetMap()->GetMapLayers().front();
	m_CollisionTileMap = m_CollisionLayer->GetTilemap();
}

bool CollisonHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
	bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
	return (x_overlaps && y_overlaps);
}

bool CollisonHandler::MapCollision(SDL_Rect a)
{
	int tileSize = 32;
	int rowCount = 60;
	int colCount = 60;

	int left_tile = a.x / tileSize;
	int right_tile = (a.x + a.w) / tileSize;
	int top_tile = a.y / tileSize;
	int bottom_tile = (a.y + a.h) / tileSize;

	if (left_tile < 0) left_tile = 0;
	if (right_tile > colCount) right_tile = colCount;
	if (top_tile < 0) top_tile = 0;
	if (bottom_tile > rowCount) bottom_tile = rowCount;

	for (int i = left_tile; i <= right_tile;i++)
	{
		for (int j = top_tile; j <= bottom_tile; j++)
		{
			if (m_CollisionTileMap[j][i] > 0) return true;
		}
	}
	return false;
}




