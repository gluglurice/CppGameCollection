#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include <graphics.h>
#include <Utils/Utils.h>

#include "CRPGBattleAssetsManager.h"

class CRPGBattleMap
{
public:
	enum MapLayer
	{
		ML_TERRAIN,
		ML_ROLES,
	};

	enum MapElem
	{
		ME_EMPTY,
		ME_TERRAIN_LAND_FLAT,
		ME_TERRAIN_LAND_GRASS,
		ME_TERRAIN_LAND_FLOWER,
	};

private:
	int m_map_layer_num;
	int m_map_width;
	int m_map_height;
	int m_tile_size;

	int m_graph_width;
	int m_graph_height;

	MapElem*** m_map_status;
	MapElem*** m_map_status_original;

public:
	/* Constructions */
	CRPGBattleMap();

	~CRPGBattleMap();

	CRPGBattleMap(const std::wstring);

	/* Logic methods */

	void InitMapStatus();

	MapElem GetMapElem(MapLayer layer, int row, int col);

	void SetMapElem(MapLayer layer, int row, int col, MapElem elem);

	/* Getters and setters */
	int  GetMapLayerNum();

	void SetMapLayerNum(int layer_num);

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

	MapElem*** GetMapStatus();

	void SetMapStatus(MapElem*** map_status);

	MapElem*** GetMapStatusOriginal();

	void SetMapStatusOriginal(MapElem*** map_status_original);
};
