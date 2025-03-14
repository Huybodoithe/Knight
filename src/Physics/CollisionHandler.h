#pragma once

#include "SDL.h"
#include "TileLayer.h"
#include "GameMap.h"
#include <vector>


class CollisonHandler
{

public:
	inline static CollisonHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisonHandler(); }

	bool MapCollision(SDL_Rect a);
	bool CheckCollision(SDL_Rect a, SDL_Rect b);


private:

	CollisonHandler();

	TileMap m_CollisionTileMap;
	TileLayer* m_CollisionLayer;
	static CollisonHandler* s_Instance;
};