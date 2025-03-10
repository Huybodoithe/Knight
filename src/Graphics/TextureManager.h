#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <map>


using namespace std;

class TextureManager
{
public:
	static TextureManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); }

	void Load(string id, string filename);//them texture vao textureMap
	void Drop(string id);//xoa texture khoi textureMap
	void Clean();//xoa du lieu cua textureMap

	//ve 1 cai gi do
	void Draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawTile(string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	SDL_Texture* GetTexture(string id) { return m_TextureMap[id]; }
private:
	TextureManager() {}

	static TextureManager* s_Instance;

	map<string, SDL_Texture*> m_TextureMap;//map chua cac texture theo id

};