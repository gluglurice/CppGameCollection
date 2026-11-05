#pragma once

#include <fstream>
#include <string>

class CSokobanV2LevelManager
{
public:
	static const std::wstring MAP_INI;

private:
	int level_num;
	int m_current_level;
	std::wstring* map_paths;

public:
	CSokobanV2LevelManager();

	~CSokobanV2LevelManager();

	std::wstring GetCurrentLevelDataPath();

	bool CheckLevelFinish(int box_not_in_target_num);

	int GetLevelNum();

	void SetLevelNum(int level_num);

	int GetCurrentLevel();

	void SetCurrentLevel(int level);

	std::wstring* GetMapPaths();

	void SetMapPaths(std::wstring* map_paths);
};
