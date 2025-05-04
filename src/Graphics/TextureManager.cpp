#include "TextureManager.h"
#include "Game.h"
#include "Camera.h"

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

bool TextureManager::ParseTextures(string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error())
	{
		cout << "Failed to load " << source << endl;
		return false;
	}
	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == string("texture"))
		{
			string id = e->Attribute("id");
			string src = e->Attribute("source");
			Load(id, src);
		}
	}

	return true;
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



void TextureManager::Draw(string id, int x, int y, int width, int height, float xScale, float yScale, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0,0,width,height };

	Vector2D cam = Camera::GetInstance()->GetPosition();
	
	SDL_Rect destRect = { x - cam.X,y - cam.Y,width * xScale,height * yScale };

	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawBackground(string id, int x, int y, int width, int height, float scrollTile, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0,0,width,height };

	//Vector2D cam = Camera::GetInstance()->GetPosition();

	//SDL_Rect destRect = { x - cam.X*scrollTile,y - cam.Y*scrollTile,width ,height };
	SDL_Rect destRect = { x ,y ,width ,height };
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { frame * width,row * height,width,height };

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect destRect = { x-cam.X,y-cam.Y,width,height };

	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawButton(string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0,0,width,height };
	SDL_Rect destRect = { x ,y,width,height };
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[id],&srcRect ,&destRect , 0, 0, flip);
}

void TextureManager::DrawTile(string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { tileSize * frame,tileSize * row,tileSize, tileSize };

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect destRect = { x-cam.X,y-cam.Y,tileSize, tileSize };
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &destRect, 0, nullptr, flip);
}