#pragma once
#include "Layer.h"
#include <vector>
#include <string>

using namespace std;

struct Tileset
{
	int FirstID, LastID;
	int RowCount, ColCount;
	int TileCount, TileSize;
	string Name, Source;
};

using TilesetList = vector<Tileset>;
using TileMap = vector<vector<int>>;


//1 layer
class TileLayer: public Layer
{
public:
	TileLayer(int tileSize, int rowCount, int colCount, TileMap tilemap, TilesetList tilesets);
	virtual void Update();
	virtual void Render();

	inline TileMap GetTilemap() { return m_Tilemap; }

private:
	int m_TileSize;
	int m_RowCount, m_ColCount;

	TileMap m_Tilemap;
	TilesetList m_Tilesets;
};
