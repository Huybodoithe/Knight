#include "TextureManager.h"
#include "Game.h"

TextureManager* TextureManager::s_Instance = nullptr;

void TextureManager::Load(string id, string filename)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == NULL) cout << "Failed to load surface: " << IMG_GetError() << endl;
	else
	{
		SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
		if (loadedTexture == NULL) cout << "Failed to load texture: " << SDL_GetError() << endl;
		else
		{
			m_TextureMap[id] = loadedTexture;
		}
	}
}

void TextureManager::Drop(string id)
{
	SDL_DestroyTexture(m_TextureMap[id]);
	m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
	for (auto& pair : m_TextureMap) {
		SDL_DestroyTexture(pair.second);
	}

	m_TextureMap.clear();
	cout << "map is cleared" << endl;
}

void TextureManager::Draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0,0,width,height };
	SDL_Rect destRect = { x,y,width,height };

	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { frame * width,row * height,width,height };
	SDL_Rect destRect = { x,y,width,height };

	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawTile(string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { tileSize * frame,tileSize * row,tileSize, tileSize };

	SDL_Rect destRect = { x,y,tileSize, tileSize };
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &destRect, 0, nullptr, flip);
}