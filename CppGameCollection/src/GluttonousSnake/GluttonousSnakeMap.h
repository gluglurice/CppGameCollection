#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include <graphics.h>

#include "../Utils.h"
#include "GluttonousSnakeUI.h"

namespace gluttonous_snake
{
	/* 路径名字长度 */
	const int PATH_NAME_LENGTH = 60;

	/* 地图层 */
	const int MAP_LAYER_NUM = 3;

	enum MapLayer
	{
		ML_TERRAIN = 0,
		ML_ENVIRONMENT = 1,
		ML_ITEM = 2,
	};

	/* 地图大小 */
	const int MAP_SCALE = 1;

	const int MAP_WIDTH = 30;
	const int MAP_HEIGHT = 30;

	const int TILE_SIZE = 32;

	const int GRAPH_WIDTH = MAP_WIDTH * TILE_SIZE * MAP_SCALE + TIP_BAR_WIDTH;
	const int GRAPH_HEIGHT = MAP_HEIGHT * TILE_SIZE * MAP_SCALE;

	/* 地图资产 */
	const int MAP_IMG_NUM = 7;
	const char MAP_PATHS[][PATH_NAME_LENGTH] = {
		"assets/GluttonousSnake/tiles/map_terrain.txt",
		"assets/GluttonousSnake/tiles/map_environment.txt",
	};
	const std::wstring map_img_paths[] = {
		L"assets/GluttonousSnake/imgs/terrain/land_flat.png",
		L"assets/GluttonousSnake/imgs/terrain/land_grass.png",
		L"assets/GluttonousSnake/imgs/terrain/land_flower.png",
		L"assets/GluttonousSnake/imgs/environment/wall_tree.png",
		L"assets/GluttonousSnake/imgs/environment/wall_trees.png",
		L"assets/GluttonousSnake/imgs/environment/transport_gate_entrance.png",
		L"assets/GluttonousSnake/imgs/environment/transport_gate_exit.png",
	};
	extern IMAGE map_imgs[MAP_IMG_NUM];

	/* 地图元素枚举 */
	enum MapEnum
	{
		ME_EMPTY = 0,

		/* 可行走 */
		ME_TERRAIN_LAND_FLAT = 1,
		ME_TERRAIN_LAND_GRASS = 2,
		ME_TERRAIN_LAND_FLOWER = 3,

		/* 不可行走 */
		ME_ENVIRONMENT_TREE = 4,
		ME_ENVIRONMENT_TREES = 5,

		/* 传送门 */
		ME_ENVIRONMENT_TRANSPORT_GATE_ENTRANCE = 6,
		ME_ENVIRONMENT_TRANSPORT_GATE_EXIT = 7,
	};

	/* 地图状态 */
	extern int map_status[MAP_LAYER_NUM][MAP_HEIGHT][MAP_WIDTH];

	/* 地图初始状态 */
	extern int map_status_original[MAP_LAYER_NUM][MAP_HEIGHT][MAP_WIDTH];
}