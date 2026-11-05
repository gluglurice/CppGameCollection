#include "CRPGBattleMap.h"
#include <stdexcept>
#include <type_traits>

CRPGBattleMap::CRPGBattleMap() {}

CRPGBattleMap::~CRPGBattleMap() {}

void CRPGBattleMap::LoadMapOriginalStatus(const std::wstring map_path)
{
	std::ifstream battle_file(map_path, std::ios::in);
	if (!battle_file.is_open())
	{
		throw std::runtime_error("Error: Unable to open map file.");
	}

	if (!(battle_file >> m_map_layer_num >> m_map_width >> m_map_height >> m_tile_size)) {
		throw std::runtime_error("Error: Reading map dimensions failed.");
	}

	SetGraphWidth(m_map_width * m_tile_size * CRPGBattleAssetsManager::SCALE + CRPGBattleAssetsManager::TIP_BAR_WIDTH);
	SetGraphHeight(m_map_height * m_tile_size * CRPGBattleAssetsManager::SCALE);

	m_map_status_original = new MapElem**[m_map_layer_num];
	m_map_status = new MapElem**[m_map_layer_num];
	for (int layer = 0; layer < m_map_layer_num; layer++)
	{
		m_map_status_original[layer] = new MapElem*[m_map_height];
		m_map_status[layer] = new MapElem * [m_map_height];
		for (int row = 0; row < m_map_height; row++)
		{
			m_map_status_original[layer][row] = new MapElem[m_map_width];
			m_map_status[layer][row] = new MapElem[m_map_width];
			for (int col = 0; col < m_map_width; col++)
			{
				m_map_status_original[layer][row][col] = ME_EMPTY;
				m_map_status[layer][row][col] = ME_EMPTY;
			}
		}
	}

	for (int row = 0; row < m_map_height; row++)
	{
		for (int col = 0; col < m_map_width; col++)
		{
			int value;
			if (!(battle_file >> value)) {
				throw std::runtime_error("Error: Reading map original status value failed.");
			}
			m_map_status_original[ML_TERRAIN][row][col] = (MapElem)value;
			m_map_status[ML_TERRAIN][row][col] = (MapElem)value;
		}
	}

	battle_file.close();
}

void CRPGBattleMap::InitMapStatus()
{
	for (int layer = 0; layer < m_map_layer_num; layer++)
	{
		for (int row = 0; row < m_map_height; row++)
		{
			for (int col = 0; col < m_map_width; col++)
			{
				m_map_status[layer][row][col] = m_map_status_original[layer][row][col];
			}
		}
	}
}

CRPGBattleMap::MapElem CRPGBattleMap::GetMapElem(MapLayer layer, int row, int col)
{
	return m_map_status[layer][row][col];
}

void CRPGBattleMap::SetMapElem(MapLayer layer, int row, int col, MapElem elem)
{
	m_map_status[layer][row][col] = elem;
}

int CRPGBattleMap::GetMapLayerNum() 
{
	return m_map_layer_num;
}

void CRPGBattleMap::SetMapLayerNum(int layer_num)
{
	m_map_layer_num = layer_num;
}

int  CRPGBattleMap::GetMapWidth()
{
	return m_map_width;
}

void CRPGBattleMap::SetMapWidth(int width)
{
	m_map_width = width;
}

int  CRPGBattleMap::GetMapHeight()
{
	return m_map_height;
}

void CRPGBattleMap::SetMapHeight(int height)
{
	m_map_height = height;
}

int  CRPGBattleMap::GetTileSize()
{
	return m_tile_size;
}

void CRPGBattleMap::SetTileSize(int tile_size)
{
	m_tile_size = tile_size;
}

int CRPGBattleMap::GetGraphWidth()
{
	return m_graph_width;
}

void CRPGBattleMap::SetGraphWidth(int width)
{
	m_graph_width = width;
}

int CRPGBattleMap::GetGraphHeight()
{
	return m_graph_height;
}

void CRPGBattleMap::SetGraphHeight(int height)
{
	m_graph_height = height;
}

CRPGBattleMap::MapElem*** CRPGBattleMap::GetMapStatus()
{
	return m_map_status;
}

void CRPGBattleMap::SetMapStatus(MapElem*** map_status)
{
	m_map_status = map_status;
}

CRPGBattleMap::MapElem*** CRPGBattleMap::GetMapStatusOriginal()
{
	return m_map_status_original;
}

void CRPGBattleMap::SetMapStatusOriginal(MapElem*** map_status_original)
{
	m_map_status_original = map_status_original;
}
