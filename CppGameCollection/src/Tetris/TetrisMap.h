#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include <graphics.h>

#include "../Utils.h"
#include "TetrisUI.h"

namespace tetris
{
	/* 地图层 */
	const int MAP_LAYER_NUM = 2;

	enum MapLayer
	{
		ML_TERRAIN = 0,
		ML_CUBE = 1,
	};

	/* 地图大小 */
	const int MAP_SCALE = 1;

	const int WALL_ROW_INDEX = 3;

	const int MAP_WIDTH = 16;
	const int MAP_HEIGHT = 30 + WALL_ROW_INDEX;

	const int TILE_SIZE = 32;

	const int GRAPH_WIDTH = MAP_WIDTH * TILE_SIZE * MAP_SCALE + TIP_BAR_WIDTH;
	const int GRAPH_HEIGHT = (MAP_HEIGHT - WALL_ROW_INDEX) * TILE_SIZE * MAP_SCALE;

	/* 地图资产 */
	const int MAP_IMG_NUM = 2;
	const std::wstring map_img_paths[] = {
		L"assets/Tetris/imgs/terrain/space.png",
		L"assets/Tetris/imgs/terrain/wall.png",
	};
	extern IMAGE map_imgs[MAP_IMG_NUM];

	/* 地图元素枚举 */
	enum MapEnum
	{
		ME_TERRAIN_SPACE,
		ME_TERRAIN_WALL,
	};

	/* 地图状态 */
	extern int map_status[MAP_LAYER_NUM][MAP_HEIGHT][MAP_WIDTH];

	/* 地图初始状态 */
	extern int map_status_original[MAP_LAYER_NUM][MAP_HEIGHT][MAP_WIDTH];
}