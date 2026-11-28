#include "Map.h"

#include "MapFC.h"
#include "Actor.h"

CMap::CMap() {}

CMap::CMap(int level, int width, int height, int tile_size, float scale, vector<vector<vector<MapElem>>>& map, CVector3D start_position_logic, ObjectsMap objects)
	: m_level(level), m_width(width), m_height(height), m_tile_size(tile_size), m_scale(scale), m_start_position_logic(start_position_logic), m_objects(objects)
{
	for (int layer = 0; layer < static_cast<int>(CMap::Layer::L_COUNT); layer++)
	{
		vector<vector<MapElem>> map_layer;
		for (int row = 0; row < height; row++)
		{
			vector<MapElem> map_row;
			for (int col = 0; col < width; col++)
			{
				map_row.push_back(map[layer][row][col]);
			}
			map_layer.push_back(map_row);
		}
		m_map.push_back(map_layer);
	}
}

CMap::~CMap() {}

bool CMap::IsWalkable(CVector3D position_logic)
{
	if (position_logic.x < 0 || position_logic.x >= m_width || position_logic.y < 0 || position_logic.y >= m_height)
	{
		return false;
	}

	bool is_terrain_walkable = m_map[CMap::L_TERRAIN][static_cast<int>(position_logic.y)][static_cast<int>(position_logic.x)] == CMap::ME_TERRAIN_37
		|| m_map[CMap::L_TERRAIN][static_cast<int>(position_logic.y)][static_cast<int>(position_logic.x)] == CMap::ME_TERRAIN_38
		|| m_map[CMap::L_TERRAIN][static_cast<int>(position_logic.y)][static_cast<int>(position_logic.x)] == CMap::ME_TERRAIN_39
		|| m_map[CMap::L_TERRAIN][static_cast<int>(position_logic.y)][static_cast<int>(position_logic.x)] == CMap::ME_TERRAIN_40
		|| m_map[CMap::L_TERRAIN][static_cast<int>(position_logic.y)][static_cast<int>(position_logic.x)] == CMap::ME_TERRAIN_49;
	
	bool is_environment_background_walkable = m_map[CMap::L_ENVIRONMENT_BACKGROUND][static_cast<int>(position_logic.y)][static_cast<int>(position_logic.x)] == CMap::ME_EMPTY;

	bool is_object_walkable = m_map[CMap::L_OBJECT][static_cast<int>(position_logic.y)][static_cast<int>(position_logic.x)] == CMap::ME_EMPTY;

	return is_environment_background_walkable && is_object_walkable && is_terrain_walkable;
}

void CMap::Draw(CMap::Layer layer)
{
	for (int row = 0; row < m_height; row++)
	{
		for (int col = 0; col < m_width; col++)
		{
			CMap::MapElem elem = m_map[layer][row][col];
			if (elem != CMap::ME_EMPTY)
			{
				Image elem_img = CMapFC::GetInstance()->GetElemImg(elem);
				CGraphic::GetInstance()->DrawTex(elem_img, CVector3D(col * m_tile_size * m_scale, row * m_tile_size * m_scale, 0.0f), CVector3D(0, 0, 0), CVector3D(0, 0, 0), CVector3D(m_scale, m_scale, 1.0f));
			}
		}
	}
}

GET_SET_FUN_DEFINE(int, CMap, m_level, Level)
GET_SET_FUN_DEFINE(int, CMap, m_width, Width)
GET_SET_FUN_DEFINE(int, CMap, m_height, Height)
GET_SET_FUN_DEFINE(int, CMap, m_tile_size, TileSize)
GET_SET_FUN_DEFINE(float, CMap, m_scale, Scale)
GET_SET_FUN_DEFINE(vector<vector<vector<CMap::MapElem>>>, CMap, m_map, Map)
GET_SET_FUN_DEFINE(CVector3D, CMap, m_start_position_logic, StartPositionLogic)
GET_SET_FUN_DEFINE(CMap::ObjectsMap, CMap, m_objects, Objects)
