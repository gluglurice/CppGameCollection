#include "Map.h"

namespace maze_rpg
{
	std::wstring map_img_paths[MAP_IMG_NUM];
	IMAGE map_imgs[MAP_IMG_NUM];

	int map_status[MAP_LAYER_NUM][MAP_HEIGHT][MAP_WIDTH];
	int map_status_original[MAP_LAYER_NUM][MAP_HEIGHT][MAP_WIDTH];

	int map_battle_status[MAP_HEIGHT][MAP_WIDTH];
	int map_battle_status_original[MAP_HEIGHT][MAP_WIDTH];
}
