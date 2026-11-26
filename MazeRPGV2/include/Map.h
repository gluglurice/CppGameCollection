#pragma once

#include <Utils.h>
#include <Graphic.h>
#include <Vector3D.h>

class CMap
{
public:
	enum MapElem
	{
		ME_EMPTY = 0,

		/* 可行走 */
		ME_TERRAIN_STEP_1 = 37,
		ME_TERRAIN_STEP_2 = 39,
		ME_TERRAIN_LAND_0 = 49,

		/* 不可行走 */
		ME_TERRAIN_TOP_0 = 1,
		ME_TERRAIN_TOP_1 = 2,
		ME_TERRAIN_TOP_2 = 3,
		ME_TERRAIN_TOP_3 = 4,
		ME_TERRAIN_TOP_4 = 5,
		ME_TERRAIN_TOP_5 = 6,
		ME_TERRAIN_TOP_6 = 14,
		ME_TERRAIN_TOP_7 = 16,
		ME_TERRAIN_TOP_8 = 17,
		ME_TERRAIN_TOP_9 = 18,
		ME_TERRAIN_TOP_10 = 27,

		ME_TERRAIN_WALL_0 = 41,
		ME_TERRAIN_WALL_1 = 58,
		ME_TERRAIN_WALL_2 = 60,
	};

GET_SET_FUN_DECLAR(int, m_level, Level)
GET_SET_FUN_DECLAR(int, m_width, Width)
GET_SET_FUN_DECLAR(int, m_height, Height)
GET_SET_FUN_DECLAR(int, m_tile_size, TileSize)
GET_SET_FUN_DECLAR(float, m_scale, Scale)
GET_SET_FUN_DECLAR(vector<vector<MapElem>>, m_map, Map)
GET_SET_FUN_DECLAR(CVector3D, m_start_position_logic, StartPositionLogic)

public:
	CMap();

	CMap(int level, int width, int height, int tile_size, float scale, const vector<vector<MapElem>>& map);

	~CMap();

	bool IsWalkable(CVector3D position_logic);

	void Draw();
};
