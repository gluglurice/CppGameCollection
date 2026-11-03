#include "Sokoban.h"

namespace sokoban
{
	#pragma region DataGame

	/****************** 常量 ******************/
	const int GRAPH_WIDTH = 460;
	const int GRAPH_HEIGHT = 320;
	const int MAP_WIDTH = 10;
	const int MAP_HEIGHT = 10;
	const int IMG_NUM = 5;
	const int IMG_PATH_LENGTH = 50;
	const int TOTAL_LEVEL_NUM = 3;

	/******************** 每关游戏获胜条件 *******************/
	int current_level = 0;
	int box_not_in_target[] = { 1, 2, 3 };
	bool game_finish = false;

	#pragma endregion

	#pragma region DataMap

	/********************* 地图资产路径 **********************/
	wchar_t map_img_paths[][IMG_PATH_LENGTH] =
	{
		L"assets/Sokoban/grass.png",
		L"assets/Sokoban/wall.png",
		L"assets/Sokoban/target.png",
		L"assets/Sokoban/box.png",
		L"assets/Sokoban/box_in_target.png",
	};

	/********************* 地图元素图片 **********************/
	IMAGE map_imgs[IMG_NUM];

	/********************* 地图元素枚举 **********************/
	enum MapElement
	{
		ME_EMPTY = 0,
		ME_GRASS = 1,
		ME_WALL = 2,
		ME_TARGET = 3,
		ME_BOX = 4,
		ME_BOX_IN_TARGET = 5,
	};

	/********************* 地图元素对应 **********************/
	std::map<int, IMAGE> img_assets;

	/*********************** 地图状态 ************************/
	int map_status[MAP_WIDTH][MAP_HEIGHT];

	/********************* 地图初始状态 **********************/
	const int map_level[][MAP_WIDTH][MAP_HEIGHT] =
	{
		{
			2,2,2,2,2,2,2,2,2,2,
			2,1,1,1,1,1,1,1,1,2,
			2,1,1,1,1,1,1,1,1,2,
			2,1,1,4,1,1,1,1,1,2,
			2,1,1,1,1,1,1,1,1,2,
			2,1,1,1,1,1,1,1,1,2,
			2,1,1,1,1,1,3,1,1,2,
			2,1,1,1,1,1,1,1,1,2,
			2,1,1,1,1,1,1,1,1,2,
			2,2,2,2,2,2,2,2,2,2
		},
		{
			2,2,2,2,2,2,2,2,2,2,
			2,1,1,1,1,1,1,1,3,2,
			2,1,4,1,1,1,1,2,2,2,
			2,1,4,1,2,1,1,2,2,2,
			2,1,1,2,2,2,1,1,1,2,
			2,2,2,2,2,1,1,1,1,2,
			0,0,0,0,2,1,1,1,1,2,
			0,0,0,0,2,2,2,2,1,2,
			0,0,0,0,0,0,2,2,3,2,
			0,0,0,0,0,0,2,2,2,2
		},
		{
			2,2,2,2,2,0,0,0,0,0,
			2,1,1,1,2,0,0,0,0,0,
			2,1,4,4,2,0,2,2,2,0,
			2,1,4,1,2,0,2,3,2,0,
			2,2,2,1,2,2,2,3,2,0,
			0,2,2,1,1,1,1,3,2,0,
			0,2,1,1,1,2,1,1,2,0,
			0,2,1,1,1,2,2,2,2,0,
			0,2,1,1,1,2,0,0,0,0,
			0,2,2,2,2,2,0,0,0,0
		},
	};

	#pragma endregion

	#pragma region DataRole

	/********************* 人物资产路径 **********************/
	wchar_t role_img_path[] = { L"assets/Sokoban/role.png" };

	/********************* 人物元素图片 *********************/
	IMAGE role_img;

	/********************* 人物朝向 *********************/
	enum RoleDirection
	{
		RD_DOWN = 0,
		RD_LEFT = 1,
		RD_RIGHT = 2,
		RD_UP = 3,
	};

	/********************* 人物坐标 *********************/
	int role_x, role_y;
	RoleDirection role_direction;

	#pragma endregion

	#pragma region Logic

	/**
	 * @brief 加载资产
	 */
	void LoadAssets() {

		/********************* 加载地图图片 **********************/
		for (int i = 0; i < IMG_NUM; i++)
		{
			loadimage(&map_imgs[i], map_img_paths[i]);
		}

		/********************* 加载人物图片 **********************/
		loadimage(&role_img, role_img_path);

		/******* 初始化地图枚举元素与地图图片资源的映射 *******/
		img_assets =
		{
			{ME_GRASS, map_imgs[0]},
			{ME_WALL, map_imgs[1]},
			{ME_TARGET, map_imgs[2]},
			{ME_BOX, map_imgs[3]},
			{ME_BOX_IN_TARGET, map_imgs[4]},
		};
	}

	/**
	 * @brief 初始化游戏状态
	 */
	void InitGameStatus()
	{
		/********************* 初始化人物坐标 **********************/
		role_x = 1, role_y = 1;
		role_direction = RD_DOWN;

		/********************* 初始化地图状态 **********************/
		memcpy(map_status, map_level[current_level], sizeof map_level[current_level]);

		/********************* 打印按键提示 **********************/
		outtextxy(GRAPH_WIDTH - 120, 120, L"移动：wasd");
		outtextxy(GRAPH_WIDTH - 120, 160, L"重置关卡：r");
	}

	/**
	 * @brief 绘制地图
	 */
	void DrawMap() {
		for (int row = 0; row < MAP_WIDTH; row++)
		{
			for (int col = 0; col < MAP_HEIGHT; col++)
			{
				putimage(
					col * map_imgs[0].getwidth(),
					row * map_imgs[0].getheight(),
					&img_assets[map_status[row][col]]
				);
			}
		}
	}

	/**
	 * @brief 绘制人物
	 */
	void DrawRole()
	{
		putimage_alpha(
			role_x * map_imgs[0].getheight(),
			role_y * map_imgs[0].getwidth(),
			&role_img,
			map_imgs[0].getheight(),
			map_imgs[0].getwidth(),
			0,
			role_direction * map_imgs[0].getheight()
		);
	}

	/**
	 * @brief 移动人物
	 * @param rd: 移动方向
	 * @param move_x: x位移量
	 * @param move_y: y位移量
	 */
	void MoveRole(RoleDirection rd, int move_x, int move_y)
	{
		role_direction = rd;
		int role_x_new = role_x + move_x;
		int role_y_new = role_y + move_y;

		/***************************** 推箱子  *****************************/
		if (map_status[role_y_new][role_x_new] == ME_BOX)
		{
			int box_x_new = role_x_new + move_x;
			int box_y_new = role_y_new + move_y;

			if (map_status[box_y_new][box_x_new] == ME_WALL
				|| map_status[box_y_new][box_x_new] == ME_BOX
				|| map_status[box_y_new][box_x_new] == ME_BOX_IN_TARGET)
			{
				return;
			}

			if (map_status[box_y_new][box_x_new] == ME_GRASS)
			{
				map_status[role_y_new][role_x_new] = ME_GRASS;
				map_status[box_y_new][box_x_new] = ME_BOX;
			}

			if (map_status[box_y_new][box_x_new] == ME_TARGET)
			{
				map_status[role_y_new][role_x_new] = ME_GRASS;
				map_status[box_y_new][box_x_new] = ME_BOX_IN_TARGET;
				box_not_in_target[current_level] -= 1;
			}
		}

		/***************************** 推已就位箱子  *****************************/
		if (map_status[role_y_new][role_x_new] == ME_BOX_IN_TARGET)
		{
			int box_x_new = role_x_new + move_x;
			int box_y_new = role_y_new + move_y;

			if (map_status[box_y_new][box_x_new] == ME_WALL
				|| map_status[box_y_new][box_x_new] == ME_BOX
				|| map_status[box_y_new][box_x_new] == ME_BOX_IN_TARGET)
			{
				return;
			}

			if (map_status[box_y_new][box_x_new] == ME_GRASS)
			{
				map_status[role_y_new][role_x_new] = ME_TARGET;
				map_status[box_y_new][box_x_new] = ME_BOX;
				box_not_in_target[current_level] += 1;
			}

			if (map_status[box_y_new][box_x_new] == ME_TARGET)
			{
				map_status[role_y_new][role_x_new] = ME_TARGET;
				map_status[box_y_new][box_x_new] = ME_BOX_IN_TARGET;
			}
		}

		/***************************** 非墙/箱子区域行走  *****************************/
		if (map_status[role_y_new][role_x_new] != ME_WALL)
		{
			role_x = role_x_new;
			role_y = role_y_new;
		}
	}

	/**
	 * @brief 判断游戏结束
	 */
	bool CheckGameWin()
	{
		if (box_not_in_target[current_level] <= 0)
		{
			if (current_level < TOTAL_LEVEL_NUM - 1)
			{
				outtextxy(
					GRAPH_WIDTH / 2 - 100,
					GRAPH_HEIGHT / 2 - 20,
					L"过关了！按任意键进入下一关..."
				);
				_getch();

				current_level++;
				cleardevice();
				FlushBatchDraw();
				InitGameStatus();
				DrawMap();
				DrawRole();
			}
			else {
				outtextxy(
					GRAPH_WIDTH / 2 - 80,
					GRAPH_HEIGHT / 2 - 20,
					L"过关了！按任意键退出游戏..."
				);
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief 游戏循环
	 */
	void GameLoop()
	{

		DrawMap();
		DrawRole();

		while (true)
		{
			char key = _getch();
			switch (key)
			{
			case 'w':
			case 'W':
				MoveRole(RD_UP, 0, -1);
				break;
			case 's':
			case 'S':
				MoveRole(RD_DOWN, 0, 1);
				break;
			case 'a':
			case 'A':
				MoveRole(RD_LEFT, -1, 0);
				break;
			case 'd':
			case 'D':
				MoveRole(RD_RIGHT, 1, 0);
				break;
			case 'r':
			case 'R':
				cleardevice();
				FlushBatchDraw();
				InitGameStatus();
				DrawMap();
				DrawRole();
				break;
			}

			DrawMap();
			DrawRole();
			/***************** 当前关卡获胜  ******************/
			game_finish = CheckGameWin();

			/***************** 全部关卡获胜  ******************/
			if (game_finish)
			{
				break;
			}
		}
	}

	#pragma endregion

	/**
	 * @brief 游戏主函数
	 */
	void Sokoban()
	{
		initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);

		LoadAssets();
		InitGameStatus();

		GameLoop();

		_getch();
		closegraph();
	}
}
