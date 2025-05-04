#include "TextManager.h"
#include "Game.h"

TextManager* TextManager::s_Instance = nullptr;

TextManager::TextManager() : m_Font(nullptr), m_QuestTexture(nullptr), m_KillsCount(nullptr), m_QuestRect({ 0,0,0,0 }), m_KillsRect({ 0,0,0,0 }) {}


void TextManager::Init(const string& fontPath)
{
    m_Font = TTF_OpenFont(fontPath.c_str(), 24);
    if (!m_Font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    SDL_Color textColor = { 0, 0, 0 };
    SDL_Surface* questSurface = TTF_RenderText_Solid(m_Font, "Kill at least 10 slimes and find the treasure", textColor);
    if (!questSurface) {
        SDL_Log("Failed to render quest text: %s", TTF_GetError());
        return;
    }

    m_QuestTexture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), questSurface);
    if (m_QuestTexture != nullptr)
    m_QuestRect = { 60, 10, questSurface->w, questSurface->h };
    SDL_FreeSurface(questSurface);

    // Initial kill count
    UpdateKillsCount(0);
}

void TextManager::Render()
{
    if (m_QuestTexture)
    {
        SDL_RenderCopy(Game::GetInstance()->GetRenderer(), m_QuestTexture, nullptr, &m_QuestRect);
        //cout << "moi" << endl;
    }
    if (m_KillsCount)
        SDL_RenderCopy(Game::GetInstance()->GetRenderer(), m_KillsCount, nullptr, &m_KillsRect);
}

void TextManager::UpdateKillsCount(int newCount)
{
    if (m_KillsCount) SDL_DestroyTexture(m_KillsCount);

    SDL_Color textColor = { 0, 0, 0 };
    std::string killText = "Kill Count " + to_string(newCount);
    SDL_Surface* killSurface = TTF_RenderText_Solid(m_Font, killText.c_str(), textColor);
    m_KillsCount = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), killSurface);
    m_KillsRect = { 60, 30, killSurface->w, killSurface->h };
    SDL_FreeSurface(killSurface);
}

void TextManager::Clean()
{
    if (m_QuestTexture) SDL_DestroyTexture(m_QuestTexture);
    if (m_KillsCount) SDL_DestroyTexture(m_KillsCount);
    if (m_Font) TTF_CloseFont(m_Font);
}
