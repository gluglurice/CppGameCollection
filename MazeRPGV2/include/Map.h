#pragma once

#include <Utils.h>
#include <Sprite.h>
#include <Graphic.h>
#include <Vector3D.h>

class CActor;

class CMap
{
public:
	enum Layer
	{
		L_TERRAIN,
		L_ENVIRONMENT_BACKGROUND,
		L_OBJECT,
		L_ENVIRONMENT_FOREGROUND,
		L_COUNT,
	};

	enum MapElem
	{
		ME_EMPTY = 0,

		/* 地面 可行走 */
		ME_TERRAIN_37 = 37,
		ME_TERRAIN_38 = 38,
		ME_TERRAIN_39 = 39,
		ME_TERRAIN_40 = 40,
		ME_TERRAIN_49 = 49,

		/* 墙 不可行走 */
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

		/* 障碍物 不可行走 */
		ME_ENVIRONMENT_56 = 56,
		ME_ENVIRONMENT_68 = 68,
		ME_ENVIRONMENT_69 = 69,
		ME_ENVIRONMENT_82 = 82,

		/* 门 可行走 */
		ME_DOOR_SINGLE_OPEN = 10,
		ME_DOOR_DOUBLE_LEFT_OPEN = 11,
		ME_DOOR_DOUBLE_RIGHT_OPEN = 12,
		ME_DOOR_WALL_1 = 133,
		ME_DOOR_WALL_2 = 134,

		/* 门 不可行走 */
		ME_DOOR_SINGLE_CLOSED = 46,
		ME_DOOR_DOUBLE_LEFT_CLOSED = 47,
		ME_DOOR_DOUBLE_RIGHT_CLOSED = 48,
	};

	using ObjectsMap = map<CVector3D, CActor*>;

GET_SET_FUN_DECLAR(int, m_level, Level)
GET_SET_FUN_DECLAR(int, m_width, Width)
GET_SET_FUN_DECLAR(int, m_height, Height)
GET_SET_FUN_DECLAR(int, m_tile_size, TileSize)
GET_SET_FUN_DECLAR(float, m_scale, Scale)
GET_SET_FUN_DECLAR(vector<vector<vector<MapElem>>>, m_map, Map)
GET_SET_FUN_DECLAR(CVector3D, m_start_position_logic, StartPositionLogic)
GET_SET_FUN_DECLAR(ObjectsMap, m_objects, Objects)

public:
	CMap();

	CMap(int level, int width, int height, int tile_size, float scale, vector<vector<vector<MapElem>>>& map, CVector3D start_position_logic, ObjectsMap objects);

	~CMap();

	bool IsWalkable(CVector3D position_logic);

	void Update();

	void Draw(Layer layer);

	void DrawObjects();
};
