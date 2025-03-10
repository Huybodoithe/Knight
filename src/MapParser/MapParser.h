#pragma once
#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml.h"


//MapParser dung de phan tich cac hinh anh tu file tmx roi them vao m_MapDict
class MapParser
{
public:
	bool Load();
	void Clean();

	inline GameMap* GetMap(string id) { return m_MapDict[id]; }
	inline static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }

private:
	bool Parse(string id, string source);
	Tileset ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);

private:
	MapParser();
	static MapParser* s_Instance;
	map<string, GameMap*> m_MapDict;  //list chua cac map
};
