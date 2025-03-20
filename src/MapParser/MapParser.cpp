#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;


GameMap* MapParser::Load(string source)
{
	GameMap* Map;
	Parse("MAP", source);
	
	Map = MapParser::GetInstance()->GetMap("MAP");
	return Map;
}

//Phan tich file tmx, phan tich cac lop cua 1 level, tao cac lop thanh 1 gamemap va them no vao m_MapDict
bool MapParser::Parse(string id, string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error())
	{
		cout << "Failed to load " << source << endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	int rowcount = 0, colcount = 0, tilesize = 0;
	root->Attribute("width", &colcount);
	root->Attribute("height", &rowcount);
	root->Attribute("tileWidth", &tilesize);

	TilesetList tilesets;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == string("tileset"))
		{
			tilesets.push_back(ParseTileset(e));
		}
	}

	GameMap* gamemap = new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == string("layer"))
		{
			TileLayer* tileLayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
			gamemap->m_MapLayers.push_back(tileLayer);
		}
	}

	m_MapDict[id] = gamemap;
	return true;
}

//Doc du lieu tileset tu xml
Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
	Tileset tileset;
	tileset.Name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid", &tileset.FirstID);

	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.LastID = tileset.FirstID + tileset.TileCount - 1;

	xmlTileset->Attribute("columns", &tileset.ColCount);
	tileset.RowCount = tileset.TileCount / tileset.ColCount;

	xmlTileset->Attribute("tilewidth", &tileset.TileSize);

	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.Source = image->Attribute("source");

	return tileset;

}


//Doc du lieu tilelayer tu xml
TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)
{
	TiXmlElement* data = __nullptr;
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == string("data"))
		{
			data = e;
			break;
		}

	}

	if (!data) cout << "Error data" << endl;
	string matrix(data->GetText());
	istringstream iss(matrix);
	string id;

	TileMap tilemap(rowcount, vector<int>(colcount, 0));

	for (int row = 0; row < rowcount; row++)
	{
		for (int col = 0; col < colcount; col++)
		{
			getline(iss, id, ',');
			stringstream convertor(id);
			convertor >> tilemap[row][col];

			if (!iss.good()) break;
		}
	}

	return new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets);
}

MapParser::MapParser()
{

}

void MapParser::Clean()
{
	map<string, GameMap*>::iterator it;
	for (it = m_MapDict.begin(); it != m_MapDict.end(); it++)
	{
		it->second = nullptr;
	}

	m_MapDict.clear();
}
