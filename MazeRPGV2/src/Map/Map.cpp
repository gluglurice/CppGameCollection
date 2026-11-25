#include "Map.h"

#include "MapFC.h"

CMap::CMap() {}

CMap::CMap(int level, int width, int height, int tile_size, float scale, const std::vector<std::vector<MapElem>>& map)
	: m_level(level), m_width(width), m_height(height), m_tile_size(tile_size), m_scale(scale)
{
	for (int row = 0; row < height; row++)
	{
		std::vector<MapElem> map_row;
		for (int col = 0; col < width; col++)
		{
			map_row.push_back(map[row][col]);
		}
		m_map.push_back(map_row);
	}
}

CMap::~CMap() {}

void CMap::Draw()
{
	for (int row = 0; row < m_height; row++)
	{
		for (int col = 0; col < m_width; col++)
		{
			CMap::MapElem elem = m_map[row][col];
			if (elem != CMap::ME_EMPTY)
			{
				Image elem_img = CMapFC::GetInstance()->GetElemImg(elem);
				CGraphic::GetInstance()->DrawTex(elem_img, D3DXVECTOR3(col * m_tile_size * m_scale, row * m_tile_size * m_scale, 0.0f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(m_scale, m_scale, 1.0f));
			}
		}
	}
}

GET_SET_FUN_DEFINE(int, CMap, m_level, Level)
GET_SET_FUN_DEFINE(int, CMap, m_width, Width)
GET_SET_FUN_DEFINE(int, CMap, m_height, Height)
GET_SET_FUN_DEFINE(int, CMap, m_tile_size, TileSize)
GET_SET_FUN_DEFINE(float, CMap, m_scale, Scale)
GET_SET_FUN_DEFINE(std::vector<std::vector<CMap::MapElem>>, CMap, m_map, Map)
