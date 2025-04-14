#pragma once

#include <map>
#include <string>
#include <iostream>
#include "SDL_mixer.h"

using namespace std;

#define FREQ 44100
#define CHUNK_SIZE 2048

using EffectMap = map<string, Mix_Chunk*>;
using MusicMap = map<string, Mix_Music*>;


class SoundManager
{
public:
	static SoundManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new SoundManager(); }

	void PlayMusic(string id);
	void LoadMusic(string id, string source);

	void PlayEffect(string id);
	void LoadEffect(string id, string source);

	void SetMusicVolume(int volume);

	void Clean();

	bool ParseSounds(string source);

private:
	SoundManager();
	static SoundManager* s_Instance;

	MusicMap m_MusicMap;
	EffectMap m_EffectMap;
};

