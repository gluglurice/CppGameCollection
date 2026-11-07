#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include <graphics.h>

#include "src/Utils/Utils.h"
#include "CSokobanV2AssetsManager.h"
#include "CSokobanV2LevelManager.h"
#include "CSokobanV2Role.h"

class CSokobanV2Map
{
public:
	enum MapElem
	{
		ME_EMPTY,
		ME_TERRAIN_GRASS,
		ME_TERRAIN_WALL,
		ME_TERRAIN_TARGET,
		ME_TERRAIN_BOX,
		ME_TERRAIN_BOX_IN_TARGET,
	};

private:
	int m_map_width;
	int m_map_height;
	int m_tile_size;

	int m_graph_width;
	int m_graph_height;

	int m_box_not_in_target_num;
	int m_box_not_in_target_num_original;

	MapElem** m_map_status;
	MapElem** m_map_status_original;

	CSokobanV2Role::Position m_role_start_position;

public:
	/* Constructions */

	CSokobanV2Map();

	~CSokobanV2Map();

	CSokobanV2Map(const std::wstring);

	/* Override operators */

	void operator=(const CSokobanV2Map& other);

	/* Logic methods */

	void InitMapStatus();

	MapElem GetMapElem(int row, int col);

	void SetMapElem(int row, int col, MapElem elem);

	/* Getters and setters */

	int  GetMapWidth();

	void SetMapWidth(int width);

	int  GetMapHeight();

	void SetMapHeight(int height);

	int GetTileSize();

	void SetTileSize(int tile_size);

	int GetGraphWidth();

	void SetGraphWidth(int width);

	int GetGraphHeight();

	void SetGraphHeight(int height);

	int GetBoxNotInTargetNum();

	void SetBoxNotInTargetNum(int box_not_in_target_num);

	int GetBoxNotInTargetNumOriginal();

	void SetBoxNotInTargetNumOriginal(int box_not_in_target_num);

	MapElem** GetMapStatus();

	void SetMapStatus(MapElem** map_status);

	MapElem** GetMapStatusOriginal();

	void SetMapStatusOriginal(MapElem** map_status_original);

	CSokobanV2Role::Position GetRoleStartPosition();

	void SetRoleStartPosition(CSokobanV2Role::Position position);
};
