#include "TileLayer.h"
#include "TextureManager.h"
#include <iostream>


TileLayer::TileLayer(int tileSize, int rowCount, int colCount, TileMap tilemap, TilesetList tilesets)
{
	m_TileSize = tileSize;
	m_RowCount = rowCount;
	m_ColCount = colCount;
	m_Tilemap = tilemap;
	m_Tilesets = tilesets;

	for (unsigned int i = 0; i < m_Tilesets.size(); i++)
	{
		TextureManager::GetInstance()->Load(m_Tilesets[i].Name,"assets/maps/" +  m_Tilesets[i].Source);

	}
}

void TileLayer::Update()
{

}

void TileLayer::Render()
{
	for (unsigned int i = 0; i < m_RowCount; i++)
	{
		for (unsigned int j = 0; j < m_ColCount; j++)
		{
			int tileID = m_Tilemap[i][j];
			
			if (tileID == 0) continue;
			else
			{
				int index = 0;
				if (m_Tilesets.size() > 1)
				{
					for (unsigned int k = 1; k < m_Tilesets.size(); k++)
					{
						if (tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID)
						{
							tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
							index = k;
							break;
						}
					}
				}
				


				Tileset ts = m_Tilesets[index];
				int tileRow = tileID / ts.ColCount;
				int tileCol = tileID - ts.ColCount * tileRow - 1;

			/*	int tileRow = (tileID - 1) / ts.ColCount;
				int tileCol = (tileID - 1) % ts.ColCount;*/

				if (tileID % ts.ColCount == 0)
				{
					tileRow--;
					tileCol = ts.RowCount - 1;
				}

				TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, j * ts.TileSize, i * ts.TileSize, tileRow, tileCol);
				
			}
		}
	}
}
