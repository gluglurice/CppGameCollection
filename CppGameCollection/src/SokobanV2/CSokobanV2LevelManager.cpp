#include "CSokobanV2LevelManager.h"

const std::wstring CSokobanV2LevelManager::MAP_INI = L"assets/SokobanV2/tiles/levels.ini";

CSokobanV2LevelManager::CSokobanV2LevelManager() : m_current_level(0)
{
	std::wifstream in_file(MAP_INI, std::ios::in);
	if (!in_file.is_open())
	{
		throw std::runtime_error("Error: Unable to open map ini file.");
	}

	if (!(in_file >> level_num)) {
		throw std::runtime_error("Error: Reading map dimensions failed.");
	}

	map_paths = new std::wstring[level_num];
	for (int i = 0; i < level_num; i++)
	{
		if (!(in_file >> map_paths[i])) {
			throw std::runtime_error("Error: Reading map path failed.");
		}
	}
	in_file.close();
}

CSokobanV2LevelManager::~CSokobanV2LevelManager() {
	delete[] map_paths;
}

std::wstring CSokobanV2LevelManager::GetCurrentLevelDataPath() {
	return map_paths[m_current_level];
}

bool CSokobanV2LevelManager::CheckLevelFinish(int box_not_in_target_num) {
	return box_not_in_target_num <= 0;
}

int CSokobanV2LevelManager::GetLevelNum() {
	return level_num;
}

void CSokobanV2LevelManager::SetLevelNum(int level_num) {
	this->level_num = level_num;
}

int CSokobanV2LevelManager::GetCurrentLevel() {
	return m_current_level;
}

void CSokobanV2LevelManager::SetCurrentLevel(int level) {
	m_current_level = level;
}

std::wstring* CSokobanV2LevelManager::GetMapPaths() {
	return map_paths;
}

void CSokobanV2LevelManager::SetMapPaths(std::wstring* map_paths) {
	this->map_paths = map_paths;
}
