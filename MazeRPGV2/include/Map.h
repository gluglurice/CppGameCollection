#pragma once

#include <Utils.h>
#include <Graphic.h>
#include <Vector3D.h>

class CMap
{
public:
	enum Layer
	{
		L_TERRAIN,
		L_ENVIRONMENT,
		L_OBJECT,
		L_COUNT,
	};

	enum MapElem
	{
		ME_EMPTY = 0,

		/* 可行走 */
		/* 地面 */
		ME_TERRAIN_37 = 37,
		ME_TERRAIN_38 = 38,
		ME_TERRAIN_39 = 39,
		ME_TERRAIN_40 = 40,
		ME_TERRAIN_49 = 49,

		/* 不可行走 */
		/* 墙 */
		ME_ENVIRONMENT_1 = 1,
		ME_ENVIRONMENT_2 = 2,
		ME_ENVIRONMENT_3 = 3,
		ME_ENVIRONMENT_4 = 4,
		ME_ENVIRONMENT_5 = 5,
		ME_ENVIRONMENT_6 = 6,

		ME_ENVIRONMENT_14 = 14,
		ME_ENVIRONMENT_15 = 15,
		ME_ENVIRONMENT_16 = 16,
		ME_ENVIRONMENT_17 = 17,
		ME_ENVIRONMENT_18 = 18,

		ME_ENVIRONMENT_26 = 26,
		ME_ENVIRONMENT_27 = 27,
		ME_ENVIRONMENT_28 = 28,
		ME_ENVIRONMENT_29 = 29,
		ME_ENVIRONMENT_30 = 30,

		ME_ENVIRONMENT_41 = 41,

		ME_ENVIRONMENT_58 = 58,
		ME_ENVIRONMENT_60 = 60,

		/* 门 */
		ME_ENVIRONMENT_10 = 10,
		ME_ENVIRONMENT_11 = 11,
		ME_ENVIRONMENT_12 = 12,
		ME_ENVIRONMENT_46 = 46,
		ME_ENVIRONMENT_47 = 47,
		ME_ENVIRONMENT_48 = 48,

		/* 障碍物 */
		ME_ENVIRONMENT_56 = 56,
		ME_ENVIRONMENT_68 = 68,
		ME_ENVIRONMENT_69 = 69,
		ME_ENVIRONMENT_82 = 82,
	};

GET_SET_FUN_DECLAR(int, m_level, Level)
GET_SET_FUN_DECLAR(int, m_width, Width)
GET_SET_FUN_DECLAR(int, m_height, Height)
GET_SET_FUN_DECLAR(int, m_tile_size, TileSize)
GET_SET_FUN_DECLAR(float, m_scale, Scale)
GET_SET_FUN_DECLAR(vector<vector<vector<MapElem>>>, m_map, Map)
GET_SET_FUN_DECLAR(CVector3D, m_start_position_logic, StartPositionLogic)

public:
	CMap();

	CMap(int level, int width, int height, int tile_size, float scale, vector<vector<vector<MapElem>>>& map, CVector3D start_position_logic);

	~CMap();

	bool IsWalkable(CVector3D position_logic);

	void Draw(Layer layer);
};
