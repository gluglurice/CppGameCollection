#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include <string>

#include <conio.h>
#include <windows.h>
#include <graphics.h>

#include "../Utils.h"
#include "TetrisMap.h"
#include "TetrisCube.h"
#include "TetrisUI.h"

namespace tetris
{
	/* 游戏全局变量 */
	const float REFRESH_TERMINAL = 500.0f;
	extern bool should_generate_cube;
	extern Cube current_cube;
	extern bool game_finish;

	enum PrintModeEnum
	{
		PME_ERASE,
		PME_PRINT,
	};

	/**
	 * @brief 加载地图资产
	 */
	void LoadMapAssets();

	/**
	 * @brief 加载物品资产
	 */
	void LoadCubeAssets();

	/**
	 * @brief 加载UI资产
	 */
	void LoadUIAssets();

	/**
	 * @brief 加载资产
	 */
	void LoadAssets();

	/**
	 * @brief 初始化游戏状态
	 */
	void InitGameStatus();

	/**
	 * @brief 绘制UI
	 */
	void DrawUI();

	/**
	 * @brief 绘制地图
	 */
	void DrawMap();

	/**
	 * @brief 绘制道具
	 */
	void DrawCube();

	/**
	 * @brief 绘制游戏结束UI
	 */
	void DrawGameFinishUI();

	/**
	 * @brief 绘制全部
	 */
	void DrawGame();

	/**
	 * @brief 把当前方块打印在地图上
	 * @param cube 
	 * @param mode
	 */
	void PrintCubeOnMap(Cube cube, PrintModeEnum mode);

	/**
	 * @brief 生成方块
	 * @param cube_type: 方块类型
	 */
	void GenerateCube(CubeEnum cube_type);

	/**
	 * @brief 移动方块
	 */
	void MoveCube();

	/**
	 * @brief 旋转方块
	 */
	void RotateCube();

	/**
	 * @brief 检查是否应该消除方块
	 * @return bool
	 */
	bool CheckShouldEraseCube();

	/**
	 * @brief 消除方块
	 */
	void EraseCube();

	/**
	 * @brief 判断游戏结束
	 * @return bool
	 */
	bool CheckGameFinish();

	/**
	 * @brief 释放游戏资源
	 */
	void Release();

	/**
	 * @brief 游戏循环
	 */
	void GameLoop();

	/**
	 * @brief 游戏主函数
	 */
	void Tetris();
}
