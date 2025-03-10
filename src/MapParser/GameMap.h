#pragma once
#include <vector>
#include "Layer.h"
#include <iostream>

using namespace std;

//1 map
class GameMap
{
public:
	void Update()
	{
		for (unsigned int i = 0; i < m_MapLayers.size();i++)
		{
			m_MapLayers[i]->Update();
		}
	}

	void Render()
	{
		
		for (unsigned int i = 0; i < m_MapLayers.size();i++)
		{
			m_MapLayers[i]->Render();
		}
	}


	vector<Layer*> GetMapLayers() { return m_MapLayers; }

private:
	friend class MapParser;
	vector<Layer*> m_MapLayers;

};