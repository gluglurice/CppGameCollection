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

#include "CRPGBattleMap.h"
#include "CRPGBattleRole.h"
#include "CRPGBattleAssetsManager.h"

class CRPGBattle
{
public:
	static constexpr float SLEEP_TIME = 500.0f;

private:
	bool m_game_finish;
	CRPGBattleAssetsManager m_assets_manager;
	CRPGBattleMap m_map;
	CRPGBattleRole m_hero;
	CRPGBattleRole m_enemy;

public:
	/* Constructions */
	CRPGBattle();

	~CRPGBattle();

	/* Logic functions */

	void InitGameStatus();

	void DrawUI();

	void DrawRoleStatus();

	void DrawBattleMap();

	void DrawBattle(CRPGBattleRole::RoleType enemy_type, CRPGBattleRole::RoleType attacker_type, bool is_attacking);

	void DrawBattleFinishUI(CRPGBattleRole::RoleType winner_type);

	void DrawAll();

	void EnterBattle(CRPGBattleRole& attacker, CRPGBattleRole& defender, CRPGBattleRole::RoleType enemy_type);

	void GameLoop();

	void RunGame();

	/* Getters and setters */
	bool GetGameFinish();

	void SetGameFinish(bool game_finish);

	CRPGBattleAssetsManager GetAssetsManager();

	void SetAssetsManager(CRPGBattleAssetsManager assets_manager);

	CRPGBattleMap GetMap();

	void SetMap(CRPGBattleMap map);

	CRPGBattleRole GetHero();

	void SetHero(CRPGBattleRole hero);

	CRPGBattleRole GetEnemy();

	void SetEnemy(CRPGBattleRole enemy);
};
