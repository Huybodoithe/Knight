#include "SeqAnimation.h"
#include "tinyxml.h"
#include "TextureManager.h"
#include <iostream>


SeqAnimation::SeqAnimation(bool repeat) : Animation(repeat)
{
}

void SeqAnimation::Update(float dt)
{
	if (m_Repeat || !m_IsEnded)
	{
		m_IsEnded = false;
		m_CurrentFrame = (SDL_GetTicks() / m_CurrentSeq.Speed) % m_CurrentSeq.FrameCount;
	}

	if (!m_Repeat && m_CurrentFrame == m_CurrentSeq.FrameCount - 1)
	{
		m_IsEnded = true;
		m_CurrentFrame = m_CurrentSeq.FrameCount - 1;
	}
}

void SeqAnimation::Parse(string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error()) cout << "Failed to load animation file: " << source << endl;

	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == string("sequence"))
		{
			Sequence seq;
			string seqID = e->Attribute("id");
			e->Attribute("speed", &seq.Speed);
			e->Attribute("width", &seq.Width);
			e->Attribute("height", &seq.Height);
			e->Attribute("frameCount", &seq.FrameCount);
			
			for (TiXmlElement* frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement())
			{
				seq.TextureIDs.push_back(frame->Attribute("textureID"));
			}
			m_SeqMap[seqID] = seq;
		}
	}
}

void SeqAnimation::SetCurrentSeq(string seqID)
{
	if (m_SeqMap.count(seqID) > 0)
	{
		m_CurrentSeq = m_SeqMap[seqID];
	}
	else
	{
		cout << "The given Sequence animation is not matching: " << seqID << endl;
	}
}

void SeqAnimation::DrawFrame(float x, float y, float xScale, float yScale, SDL_RendererFlip flip)
{
	TextureManager::GetInstance()->Draw(m_CurrentSeq.TextureIDs[m_CurrentFrame], x, y, m_CurrentSeq.Width, m_CurrentSeq.Height, xScale, yScale, flip);
}
