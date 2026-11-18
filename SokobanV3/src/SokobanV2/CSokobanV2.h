#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#include <regex>

#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <Utils/Utils.h>

#include "CSokobanV2AssetsManager.h"
#include "CSokobanV2LevelManager.h"
#include "CSokobanV2Map.h"
#include "CSokobanV2Role.h"

class CSokobanV2
{
private:
	bool m_game_finish;

	CSokobanV2AssetsManager m_assets_manager;
	CSokobanV2LevelManager m_level_manager;

	CSokobanV2Map m_map;
	CSokobanV2Role m_role;

public:
	/* Constructions */
	CSokobanV2();

	~CSokobanV2();

	/* Logic functions */

	void InitGameStatus();

	void DrawUI();

	void DrawMap();

	void DrawRole();

	void DrawLevelFinishUI();

	void DrawGameFinishUI();

	void DrawAll();

	void GameLoop();

	void RunGame();

	/* Getters and setters */
	bool GetGameFinish();

	void SetGameFinish(bool game_finish);

	CSokobanV2AssetsManager GetAssetsManager();

	void SetAssetsManager(CSokobanV2AssetsManager assets_manager);

	CSokobanV2LevelManager GetLevelManager();

	void SetLevelManager(CSokobanV2LevelManager level_manager);

	CSokobanV2Map GetMap();

	void SetMap(CSokobanV2Map map);

	CSokobanV2Role GetRole();

	void SetRole(CSokobanV2Role role);
};
