#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include <string>

#include <conio.h>
#include <windows.h>
#include <graphics.h>

#include "src/Utils/Utils.h"
#include "GluttonousSnakeMap.h"
#include "GluttonousSnakeSnake.h"
#include "GluttonousSnakeItem.h"
#include "GluttonousSnakeUI.h"

namespace gluttonous_snake
{
	/* 游戏全局变量 */
	const float REFRESH_TERMINAL = 500.0f;

	/* 传送门坐标映射 */
	extern std::map<Position, Position> transport_gate_map;

	extern float item_generate_terminal;
	extern bool game_finish;

	/**
	 * @brief 加载地图资产
	 */
	void LoadMapAssets();

	/**
	 * @brief 加载蛇的资产
	 */
	void LoadSnakeAssets();

	/**
	 * @brief 加载物品资产
	 */
	void LoadItemAssets();

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
	 * @brief 绘制蛇
	 */
	void DrawSnake();

	/**
	 * @brief 绘制道具
	 */
	void DrawItem();

	/**
	 * @brief 绘制游戏结束UI
	 */
	void DrawGameFinishUI();

	/**
	 * @brief 绘制全部
	 */
	void DrawGame();

	/**
	 * @brief 检查给定位置上是否存在环境元素
	 * @param position: 要检查的位置
	 * @return bool
	 */
	bool CheckCollisionOnEnvironment(Position position);

	/**
	 * @brief 检查给定位置上是否存在蛇
	 * @param position: 要检查的位置
	 * @return bool
	 */
	bool CheckCollisionOnSnakeBody(Position position);

	/**
	 * @brief 检查给定位置上是否存在道具
	 * @param position: 要检查的位置
	 * @return bool
	 */
	bool CheckCollisionOnItem(Position position);

	/**
	 * @brief 生成物品
	 * @param item_type: 物品类型
	 */
	void GenerateItem(ItemEnum item_type);

	/**
	 * @brief 拾取物品
	 */
	void PickUpItem();

	/**
	 * @brief 蛇吃下食物后变长
	 */
	void SnakeGrow();

	/**
	 * @brief 返回传送门出口坐标
	 */
	Position TransportSnake(Position entrance_position);

	/**
	 * @brief 移动蛇
	 * @param direction: 移动方向
	 */
	void MoveSnake(SnakeDirection direction);

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
	void GluttonousSnake();
}
