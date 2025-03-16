#pragma once
#include <map>
#include "SDL.h"
#include <string>
#include <vector>
#include "Animation.h"

using namespace std;

struct Sequence
{
	int Speed;
	int FrameCount;
	int Width, Height;
	vector<string> TextureIDs;
};

class SeqAnimation : public Animation
{
public:
	SeqAnimation(bool repeat = true);

	virtual void Update(float dt);
	void Parse(string source);
	void SetCurrentSeq(string seqID);
	void SetRepeat(bool repeat) { m_Repeat = repeat; }
	void DrawFrame(float x, float y, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	Sequence m_CurrentSeq;
	map<string, Sequence> m_SeqMap;
};