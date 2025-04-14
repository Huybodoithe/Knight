#include "SoundManager.h"
#include "tinyxml.h"

SoundManager* SoundManager::s_Instance = nullptr;


SoundManager::SoundManager()
{
	if (Mix_OpenAudio(FREQ, MIX_DEFAULT_FORMAT, 2, CHUNK_SIZE), 0)
	{
		cout << Mix_GetError() << endl;
	}
}

void SoundManager::PlayMusic(string id)
{
	if (Mix_PlayMusic(m_MusicMap[id], -1) == -1)
	{
		cout << Mix_GetError() << endl;
	}
}

void SoundManager::LoadMusic(string id, string source)
{
	Mix_Music* music = Mix_LoadMUS(source.c_str());
	if (music != nullptr) m_MusicMap[id] = music;
	else cout << Mix_GetError() << ": " << source << endl;
}

void SoundManager::PlayEffect(string id)
{
	if(Mix_PlayChannel(-1, m_EffectMap[id], 0) == -1)
	{
		cout << Mix_GetError() << endl;
	}
}

void SoundManager::LoadEffect(string id, string source)
{
	Mix_Chunk* effect = Mix_LoadWAV(source.c_str());
	if (effect != nullptr) m_EffectMap[id] = effect;
	else cout << Mix_GetError() << ": " << source << endl;
}

void SoundManager::SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

bool SoundManager::ParseSounds(string source)
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
		if (e->Value() == string("effect"))
		{
			LoadEffect(e->Attribute("id"), e->Attribute("source"));
			continue;
		}

		if (e->Value() == string("music"))
		{
			LoadMusic(e->Attribute("id"), e->Attribute("source"));
			continue;
		}
	}
	cout << source << " Parsed!" << endl;
	return true;
}

void SoundManager::Clean()
{
	for (auto& pair : m_MusicMap)
	{
		Mix_FreeMusic(pair.second);
	}
	for (auto& pair : m_EffectMap)
	{
		Mix_FreeChunk(pair.second);
	}

	m_MusicMap.clear();
	m_EffectMap.clear();

	cout << "sound system is cleared!" << endl;
}


