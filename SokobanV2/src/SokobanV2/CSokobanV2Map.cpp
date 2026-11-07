#include "CSokobanV2Map.h"

CSokobanV2Map::CSokobanV2Map() {}

CSokobanV2Map::~CSokobanV2Map()
{
	for (int row = 0; row < m_map_height; row++)
	{
		delete[] m_map_status[row];
		delete[] m_map_status_original[row];
	}
	delete[] m_map_status;
	delete[] m_map_status_original;
}

CSokobanV2Map::CSokobanV2Map(const std::wstring map_path)
{
	m_box_not_in_target_num = 0;
	m_box_not_in_target_num_original = 0;

	std::ifstream battle_file(map_path, std::ios::in);
	if (!battle_file.is_open())
	{
		throw std::runtime_error("Error: Unable to open map file.");
	}

	if (!(battle_file >> m_map_width >> m_map_height >> m_tile_size >> m_role_start_position.x >> m_role_start_position.y)) {
		throw std::runtime_error("Error: Reading map dimensions failed.");
	}

	SetGraphWidth(m_map_width * m_tile_size * CSokobanV2AssetsManager::SCALE + CSokobanV2AssetsManager::TIP_BAR_WIDTH);
	SetGraphHeight(m_map_height * m_tile_size * CSokobanV2AssetsManager::SCALE);

	m_map_status_original = new MapElem*[m_map_height];
	m_map_status = new MapElem * [m_map_height];
	for (int row = 0; row < m_map_height; row++)
	{
		m_map_status_original[row] = new MapElem[m_map_width];
		m_map_status[row] = new MapElem[m_map_width];
		for (int col = 0; col < m_map_width; col++)
		{
			m_map_status_original[row][col] = ME_EMPTY;
			m_map_status[row][col] = ME_EMPTY;
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
			m_map_status_original[row][col] = (MapElem)value;
			m_map_status[row][col] = (MapElem)value;
			if (m_map_status_original[row][col] == ME_TERRAIN_BOX)
			{
				m_box_not_in_target_num++;
				m_box_not_in_target_num_original++;
			}
		}
	}

	battle_file.close();
}

void CSokobanV2Map::operator=(const CSokobanV2Map& other)
{
	m_map_width = other.m_map_width;
	m_map_height = other.m_map_height;
	m_tile_size = other.m_tile_size;
	m_graph_width = other.m_graph_width;
	m_graph_height = other.m_graph_height;
	m_box_not_in_target_num = other.m_box_not_in_target_num;
	m_box_not_in_target_num_original = other.m_box_not_in_target_num_original;
	for (int row = 0; row < m_map_height; row++)
	{
		for (int col = 0; col < m_map_width; col++)
		{
			m_map_status[row][col] = other.m_map_status[row][col];
			m_map_status_original[row][col] = other.m_map_status_original[row][col];
		}
	}
	m_role_start_position = other.m_role_start_position;
}

void CSokobanV2Map::InitMapStatus()
{
	for (int row = 0; row < m_map_height; row++)
	{
		for (int col = 0; col < m_map_width; col++)
		{
			m_map_status[row][col] = m_map_status_original[row][col];
		}
	}
	m_box_not_in_target_num = m_box_not_in_target_num_original;
}

CSokobanV2Map::MapElem CSokobanV2Map::GetMapElem(int row, int col)
{
	return m_map_status[row][col];
}

void CSokobanV2Map::SetMapElem(int row, int col, MapElem elem)
{
	m_map_status[row][col] = elem;
}

int  CSokobanV2Map::GetMapWidth()
{
	return m_map_width;
}

void CSokobanV2Map::SetMapWidth(int width)
{
	m_map_width = width;
}

int  CSokobanV2Map::GetMapHeight()
{
	return m_map_height;
}

void CSokobanV2Map::SetMapHeight(int height)
{
	m_map_height = height;
}

int  CSokobanV2Map::GetTileSize()
{
	return m_tile_size;
}

void CSokobanV2Map::SetTileSize(int tile_size)
{
	m_tile_size = tile_size;
}

int CSokobanV2Map::GetGraphWidth()
{
	return m_graph_width;
}

void CSokobanV2Map::SetGraphWidth(int width)
{
	m_graph_width = width;
}

int CSokobanV2Map::GetGraphHeight()
{
	return m_graph_height;
}

void CSokobanV2Map::SetGraphHeight(int height)
{
	m_graph_height = height;
}

int CSokobanV2Map::GetBoxNotInTargetNum()
{
	return m_box_not_in_target_num;
}

void CSokobanV2Map::SetBoxNotInTargetNum(int box_not_in_target_num)
{
	m_box_not_in_target_num = box_not_in_target_num;
}

int CSokobanV2Map::GetBoxNotInTargetNumOriginal()
{
	return m_box_not_in_target_num_original;
}

void CSokobanV2Map::SetBoxNotInTargetNumOriginal(int box_not_in_target_num)
{
	m_box_not_in_target_num_original = box_not_in_target_num;
}

CSokobanV2Map::MapElem** CSokobanV2Map::GetMapStatus()
{
	return m_map_status;
}

void CSokobanV2Map::SetMapStatus(MapElem** map_status)
{
	for (int row = 0; row < m_map_height; row++)
	{
		for (int col = 0; col < m_map_width; col++)
		{
			m_map_status[row][col] = map_status[row][col];
		}
	}
}

CSokobanV2Map::MapElem** CSokobanV2Map::GetMapStatusOriginal()
{
	return m_map_status_original;
}

void CSokobanV2Map::SetMapStatusOriginal(MapElem** map_status_original)
{
	for (int row = 0; row < m_map_height; row++)
	{
		for (int col = 0; col < m_map_width; col++)
		{
			m_map_status_original[row][col] = map_status_original[row][col];
		}
	}
}

CSokobanV2Role::Position CSokobanV2Map::GetRoleStartPosition()
{
	return m_role_start_position;
}

void CSokobanV2Map::SetRoleStartPosition(CSokobanV2Role::Position position)
{
	m_role_start_position = position;
}
