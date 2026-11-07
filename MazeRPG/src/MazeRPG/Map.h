#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include <graphics.h>

#include "src/Utils/Utils.h"

namespace maze_rpg
{
	/* 路径名字长度 */
	const int PATH_NAME_LENGTH = 60;

	/* 地图大小 */
	const int MAP_SCALE = 2;

	const int MAP_LAYER_NUM = 4;

	const int MAP_WIDTH = 30;
	const int MAP_HEIGHT = 17;

	const int TILE_SIZE = 16;

	const int TIP_BAR_WIDTH = 200;

	const int GRAPH_WIDTH = MAP_WIDTH * TILE_SIZE * MAP_SCALE + TIP_BAR_WIDTH;
	const int GRAPH_HEIGHT = MAP_HEIGHT * TILE_SIZE * MAP_SCALE;

	/* 地图资产 */
	const int MAP_IMG_NUM = 198;
	const char MAP_PATHS[][PATH_NAME_LENGTH] = {
		"assets/MazeRPG/img/Tiled/map_level_1_terrain.txt",
		"assets/MazeRPG/img/Tiled/map_level_1_rail.txt",
		"assets/MazeRPG/img/Tiled/map_level_1_environment.txt",
		"assets/MazeRPG/img/Tiled/map_level_1_roles.txt",
	};
	const char MAP_BATTLE_PATH[] = {
		"assets/MazeRPG/img/Tiled/map_battle.txt"
	};
	const std::wstring MAP_IMGS_ROOT_PATH = L"assets/MazeRPG/img/Tiles";

	extern std::wstring map_img_paths[MAP_IMG_NUM];
	extern IMAGE map_imgs[MAP_IMG_NUM];

	/* 地图层枚举 */
	enum MapLayer
	{
		ML_TERRAIN = 0,
		ML_RAIL = 1,
		ML_ENVIRONMENT = 2,
		ML_ROLES = 3,
	};

	/* 地图元素枚举 */
	enum MapElem
	{
		ME_EMPTY = 0,

		/* 可行走 */
		ME_TERRAIN_LAND_FLAT = 1,
		ME_TERRAIN_LAND_GRASS = 2,
		ME_TERRAIN_LAND_FLOWER = 3,

		ME_RAIL_BRIDGE = 131,
		ME_RAIL_HORIZONTAL_MID = 111,
		ME_RAIL_HORIZONTAL_RIGHT = 112,
		ME_RAIL_VERTICAL_MID = 145,
		ME_RAIL_TURN_UPPER_LEFT = 128,
		ME_RAIL_TURN_UPPER_MID = 129,
		ME_RAIL_TURN_UPPER_RIGHT = 130,
		ME_RAIL_TURN_LOWER_LEFT = 164,
		ME_RAIL_TURN_LOWER_RIGHT = 166,

		/* 不可行走 */
		ME_TERRAIN_RIVER_UPPER_LEFT = 4,
		ME_TERRAIN_RIVER_UPPER_RIGHT = 5,
		ME_TERRAIN_RIVER_LOWER_LEFT = 22,
		ME_TERRAIN_RIVER_LOWER_RIGHT = 23,
		ME_TERRAIN_RIVER_UP = 40,
		ME_TERRAIN_RIVER_MID = 58,
		ME_TERRAIN_RIVER_LOW = 76,

		ME_TERRAIN_POOL_UPPER_LEFT = 19,
		ME_TERRAIN_POOL_UPPER_MID = 20,
		ME_TERRAIN_POOL_UPPER_RIGHT = 21,
		ME_TERRAIN_POOL_MID_LEFT = 37,
		ME_TERRAIN_POOL_MID_MID = 38,
		ME_TERRAIN_POOL_MID_RIGHT = 39,
		ME_TERRAIN_POOL_LOWER_LEFT = 55,
		ME_TERRAIN_POOL_LOWER_MID = 56,
		ME_TERRAIN_POOL_LOWER_RIGHT = 57,
		ME_TERRAIN_POOL_TURN_LOWER_LEFT = 92,

		ME_RAIL_POOL_UNDER_BRIDGE = 149,

		ME_ENVIRONMENT_BARN = 6,
		ME_ENVIRONMENT_TREE = 95,
		ME_ENVIRONMENT_TREES = 113,

		ME_ENVIRONMENT_HERO_FLAG = 89,
		ME_ENVIRONMENT_HERO_CASTLE = 87,
		ME_ENVIRONMENT_ENEMY_CASTLE = 51,

		/* 人物 */
		ME_ROLES_HERO = 180,
		ME_ROLES_ENEMY_SWORD = 144,
		ME_ROLES_ENEMY_GUN = 143,
	};

	/* 地图状态 */
	extern int map_status[MAP_LAYER_NUM][MAP_HEIGHT][MAP_WIDTH];

	/* 地图初始状态 */
	extern int map_status_original[MAP_LAYER_NUM][MAP_HEIGHT][MAP_WIDTH];

	/* 战斗地图状态 */
	extern int map_battle_status[MAP_HEIGHT][MAP_WIDTH];

	/* 战斗地图初始状态 */
	extern int map_battle_status_original[MAP_HEIGHT][MAP_WIDTH];
}