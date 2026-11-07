#include "GluttonousSnakeMap.h"

namespace gluttonous_snake
{
	IMAGE map_imgs[MAP_IMG_NUM];

	int map_status[MAP_LAYER_NUM][MAP_HEIGHT][MAP_WIDTH] = {};
	int map_status_original[MAP_LAYER_NUM][MAP_HEIGHT][MAP_WIDTH] = {};
}
