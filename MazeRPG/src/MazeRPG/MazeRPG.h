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

#include "Map.h"
#include "Role.h"

namespace maze_rpg
{
	const float SLEEP_TIME = 500.0f;

	/* 游戏获胜条件 */
	extern int enemy_num;
	extern std::map<Position, int> enemy_map;
	extern bool game_finish;

	/**
	 * @brief 加载地图资产
	 */
	void LoadMapAssets();

	/**
	 * @brief 加载人物资产
	 */
	void LoadRoleAssets();

	/**
	 * @brief 加载资产
	 */
	void LoadAssets();

	/**
	 * @brief 初始化游戏状态
	 */
	void InitGameStatus();

	/**
	 * @brief 绘制提示
	 */
	void DrawTips();

	/**
	 * @brief 绘制地图
	 */
	void DrawMap();

	/**
	 * @brief 绘制人物
	 * @param role
	 * @param role_img
	 * @param TILE_SIZE
	 */
	void DrawRole(Role role, IMAGE role_img, const int TILE_SIZE);

	/**
	 * @brief 绘制全部人物
	 */
	void DrawRole();

	/**
	 * @brief 绘制人物状态
	 */
	void DrawRoleStatus();

	/**
	 * @brief 绘制战斗地图
	 */
	void DrawBattleMap();

	/**
	 * @brief 绘制战斗过程
	 * @param enemy_type 
	 * @param attacker_type 
	 * @param is_attacking 
	 */
	void DrawBattle(RoleType enemy_type, RoleType attacker_type, bool is_attacking);

	/**
	 * @brief 判断地形是否可行走
	 * @param type 地形类型
	 * @return bool is_walkable
	 */
	bool CheckMapWalkable(int type);

	/**
	 * @brief 发起攻击
	 * @param attacker 
	 * @param defender 
	 */
	void Attack(Role& attacker, Role& defender);

	/**
	 * @brief 进入回合制
	 * @param attacker 
	 * @param defender 
	 */
	void EnterBattle(Role& attacker, Role& defender);

	/**
	 * @brief 移动人物
	 * @param rd: 移动方向
	 * @param move_x: x位移量
	 * @param move_y: y位移量
	 */
	void MoveRole(RoleDirection rd, int move_x, int move_y);

	/**
	 * @brief 判断游戏结束
	 */
	bool CheckGameWin();

	/**
	 * @brief 游戏循环
	 */
	void GameLoop();

	/**
	 * @brief 游戏主函数
	 */
	void MazeRPG();
}
