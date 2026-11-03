#include "GluttonousSnake.h"

namespace gluttonous_snake
{
	float item_generate_terminal = 2000.0f;

	std::map<Position, Position> transport_gate_map;

	bool game_finish = false;

	void LoadMapAssets()
	{
		/* 加载地图图片 */
		for (int i = 0; i < MAP_IMG_NUM; i++)
		{
			loadimage(&map_imgs[i], map_img_paths[i].c_str());
		}

		/* 加载地图原始状态数据 */
		Position transport_gate_entrance(-1, -1);
		Position transport_gate_exit(-1, -1);
		for (int layer = 0; layer < MAP_LAYER_NUM - 1; layer++)
		{
			std::ifstream map_file(MAP_PATHS[layer], std::ios::in);
			if (!map_file.is_open())
			{
				std::cerr << "打开" << MAP_PATHS[layer] << "失败" << std::endl;
				return;
			}
			for (int row = 0; row < MAP_HEIGHT; row++)
			{
				for (int col = 0; col < MAP_WIDTH; col++)
				{
					map_file >> map_status_original[layer][row][col];
					if (layer == ML_ENVIRONMENT)
					{
						if (map_status_original[layer][row][col] == ME_ENVIRONMENT_TRANSPORT_GATE_ENTRANCE)
						{
							transport_gate_entrance = Position(col, row);
						}
						else if (map_status_original[layer][row][col] == ME_ENVIRONMENT_TRANSPORT_GATE_EXIT)
						{
							transport_gate_exit = Position(col, row);
						}
					}
				}
			}
			map_file.close();
		}
		transport_gate_map[transport_gate_entrance] = transport_gate_exit;
	}

	void LoadSnakeAssets()
	{
		/* 加载蛇的图片 */
		for (int i = 0; i < SNAKE_IMG_NUM; i++)
		{
			loadimage(&snake_imgs[i], snake_img_paths[i].c_str());
		}
	}

	void LoadItemAssets()
	{
		/* 加载物品的图片 */
		for (int i = 0; i < ITEM_IMG_NUM; i++)
		{
			loadimage(&item_imgs[i], item_img_paths[i].c_str());
		}
	}

	void LoadUIAssets()
	{
		/* 加载UI图片 */
		for (int i = 0; i < UI_IMG_NUM; i++)
		{
			loadimage(&ui_imgs[i], ui_img_paths[i].c_str());
		}
	}

	void LoadAssets()
	{
		LoadMapAssets();
		LoadSnakeAssets();
		LoadItemAssets();
		LoadUIAssets();
	}

	void InitGameStatus()
	{
		/* 初始化地图状态 **/
		memcpy(map_status, map_status_original, sizeof map_status_original);

		/* 初始化蛇 */
		snake = Snake(3, 1.0f, 10, 10, SD_DOWN);
	}

	void  DrawUI()
	{
		/* 绘制UI背景 */
		putimage(
			MAP_WIDTH * TILE_SIZE * MAP_SCALE,
			0,
			&ui_imgs[UII_BACKGROUND]
		);

		/* 绘制UI按键 */
		const int UI_KEY_WIDTH_MID = 130;
		const int UI_KEY_SIZE = 48;
		const int UI_KEY_SCALE = 2;
		const float UI_KEY_HEIGHT_FACTOR = 0.6f;

		putimage_alpha_zoom(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			&ui_imgs[UII_KEYBOARD_W]
		);
		putimage_alpha_zoom(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			&ui_imgs[UII_KEYBOARD_S]
		);
		putimage_alpha_zoom(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID - UI_KEY_SIZE,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			&ui_imgs[UII_KEYBOARD_A]
		);
		putimage_alpha_zoom(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID + UI_KEY_SIZE,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			&ui_imgs[UII_KEYBOARD_D]
		);

		setbkmode(TRANSPARENT);
		settextcolor(RGB(0x6D, 0x4B, 0x27));
		settextstyle(20, 0, _T("微软雅黑"), 0, 0, FW_BOLD, FALSE, FALSE, FALSE);
		outtextxy(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID + 16,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE * UI_KEY_SCALE + 16,
			_T("移动")
		);

		/* 绘制UI图例 */
		const int UI_FIGURE_WIDTH_MID = 160;
		const float UI_FIGURE_HEIGHT_FACTOR = 0.8f;

		putimage_alpha_zoom(
			GRAPH_WIDTH - UI_FIGURE_WIDTH_MID,
			GRAPH_HEIGHT * UI_FIGURE_HEIGHT_FACTOR,
			TILE_SIZE * MAP_SCALE,
			TILE_SIZE * MAP_SCALE,
			&map_imgs[ME_ENVIRONMENT_TRANSPORT_GATE_ENTRANCE - 1]
		);
		outtextxy(
			GRAPH_WIDTH - UI_FIGURE_WIDTH_MID + 48,
			GRAPH_HEIGHT * UI_FIGURE_HEIGHT_FACTOR + 6,
			_T("传送门入口")
		);

		putimage_alpha_zoom(
			GRAPH_WIDTH - UI_FIGURE_WIDTH_MID,
			GRAPH_HEIGHT * UI_FIGURE_HEIGHT_FACTOR + 48,
			TILE_SIZE * MAP_SCALE,
			TILE_SIZE * MAP_SCALE,
			&map_imgs[ME_ENVIRONMENT_TRANSPORT_GATE_EXIT - 1]
		);
		outtextxy(
			GRAPH_WIDTH - UI_FIGURE_WIDTH_MID + 48,
			GRAPH_HEIGHT * UI_FIGURE_HEIGHT_FACTOR + 48 + 6,
			_T("传送门出口")
		);

		/* 绘制UI提示文本 */
		const int UI_TIPS_WIDTH_MID = 140;
		const float UI_TIPS_HEIGHT_FACTOR = 0.4f;

		outtextxy(
			GRAPH_WIDTH - UI_TIPS_WIDTH_MID,
			GRAPH_HEIGHT * UI_TIPS_HEIGHT_FACTOR,
			_T("吃心心♥吧！")
		);
	}

	void DrawMap()
	{
		for (int layer = 0; layer < MAP_LAYER_NUM; layer++)
		{
			for (int row = 0; row < MAP_HEIGHT; row++)
			{
				for (int col = 0; col < MAP_WIDTH; col++)
				{
					putimage_alpha_zoom(
						col * TILE_SIZE * MAP_SCALE,
						row * TILE_SIZE * MAP_SCALE,
						TILE_SIZE * MAP_SCALE,
						TILE_SIZE * MAP_SCALE,
						&map_imgs[map_status[layer][row][col] - 1]
					);
				}
			}
		}
	}

	void DrawSnake()
	{
		bool is_head = true;
		SnakeNode* current = snake.head;
		while (current != nullptr)
		{
			SnakeImg snake_img;

			/* 根据蛇头方向选择图像 */
			if (is_head)
			{
				switch (current->direction)
				{
				case SD_DOWN:
					snake_img = SI_SNAKE_HEAD_DOWN;
					break;
				case SD_UP:
					snake_img = SI_SNAKE_HEAD_UP;
					break;
				case SD_LEFT:
					snake_img = SI_SNAKE_HEAD_LEFT;
					break;
				case SD_RIGHT:
					snake_img = SI_SNAKE_HEAD_RIGHT;
					break;
				}
				is_head = false;
			}
			/* 根据蛇尾方向选择图像 */
			else if (current->next == nullptr)
			{
				switch (current->direction)
				{
				case SD_DOWN:
					snake_img = SI_SNAKE_BODY_TAIL_DOWN;
					break;
				case SD_UP:
					snake_img = SI_SNAKE_BODY_TAIL_UP;
					break;
				case SD_LEFT:
					snake_img = SI_SNAKE_BODY_TAIL_LEFT;
					break;
				case SD_RIGHT:
					snake_img = SI_SNAKE_BODY_TAIL_RIGHT;
					break;
				}
			}
			/* 根据蛇身选择图像 */
			else
			{
				snake_img = SI_SNAKE_BODY;
			}

			/* 绘制蛇的节点图像 */
			putimage_alpha_zoom(
				current->position.x * TILE_SIZE * MAP_SCALE,
				current->position.y * TILE_SIZE * MAP_SCALE,
				TILE_SIZE * MAP_SCALE,
				TILE_SIZE * MAP_SCALE,
				&snake_imgs[snake_img]
			);
			current = current->next;
		}
	}

	void DrawItem()
	{
		for (int row = 0; row < MAP_HEIGHT; row++)
		{
			for (int col = 0; col < MAP_WIDTH; col++)
			{
				putimage_alpha_zoom(
					col * TILE_SIZE * MAP_SCALE,
					row * TILE_SIZE * MAP_SCALE,
					TILE_SIZE * MAP_SCALE,
					TILE_SIZE * MAP_SCALE,
					&item_imgs[map_status[ML_ITEM][row][col] - 1]
				);
			}
		}
	}

	void DrawGameFinishUI()
	{
		const int UI_TIPS_WIDTH_MID = 150;
		const float UI_TIPS_HEIGHT_FACTOR = 0.4f;

		setbkcolor(RGB(0xFF, 0xF1, 0xD2));
		setbkmode(OPAQUE);
		settextcolor(RGB(0x6D, 0x4B, 0x27));
		settextstyle(20, 0, _T("微软雅黑"), 0, 0, FW_BOLD, FALSE, FALSE, FALSE);
		outtextxy(
			GRAPH_WIDTH - UI_TIPS_WIDTH_MID,
			GRAPH_HEIGHT * UI_TIPS_HEIGHT_FACTOR,
			_T("好像有点鼠了...")
		);
	}

	void DrawGame()
	{
		BeginBatchDraw();
		DrawUI();
		DrawMap();
		DrawSnake();
		DrawItem();
		if (CheckGameFinish())
		{
			DrawGameFinishUI();
		}
		FlushBatchDraw();
	}

	bool CheckCollisionOnEnvironment(Position position)
	{
		if (position.x < 0 || position.x >= MAP_WIDTH || position.y < 0 || position.y >= MAP_HEIGHT)
		{
			return true;
		}
		if (map_status[ML_ENVIRONMENT][position.y][position.x] == ME_ENVIRONMENT_TREE
			|| map_status[ML_ENVIRONMENT][position.y][position.x] == ME_ENVIRONMENT_TREES
			|| map_status[ML_ENVIRONMENT][position.y][position.x] == ME_ENVIRONMENT_TRANSPORT_GATE_ENTRANCE
			|| map_status[ML_ENVIRONMENT][position.y][position.x] == ME_ENVIRONMENT_TRANSPORT_GATE_EXIT)
		{
			return true;
		}
		return false;
	}

	bool CheckCollisionOnSnakeBody(Position position)
	{
		SnakeNode* current = snake.head;
		while (current != nullptr)
		{
			if (current->position.x == position.x && current->position.y == position.y)
			{
				return true;
			}
			current = current->next;
		}
		return false;
	}

	bool CheckCollisionOnItem(Position position)
	{
		if (map_status[ML_ITEM][position.y][position.x] != ME_EMPTY)
		{
			return true;
		}
		return false;
	}

	void GenerateItem(ItemEnum item_type)
	{
		int x = rand() % (MAP_WIDTH - 2) + 1;
		int y = rand() % (MAP_HEIGHT - 2) + 1;
		Position item_position(x, y);

		while (CheckCollisionOnEnvironment(item_position)
			|| CheckCollisionOnSnakeBody(item_position)
			|| CheckCollisionOnItem(item_position))
		{
			x = rand() % (MAP_WIDTH - 2) + 1;
			y = rand() % (MAP_HEIGHT - 2) + 1;
			item_position.x = x;
			item_position.y = y;
		}

		map_status[ML_ITEM][item_position.y][item_position.x] = item_type;
	}

	void PickUpItem(Position position)
	{
		if (map_status[ML_ITEM][position.y][position.x] == IE_FOOD)
		{
			SnakeGrow();
			map_status[ML_ITEM][position.y][position.x] = ME_EMPTY;
		}
		else if (map_status[ML_ITEM][position.y][position.x] == IE_GAS)
		{
			snake.velocity += 0.5f;
			map_status[ML_ITEM][position.y][position.x] = ME_EMPTY;
		}
	}

	void SnakeGrow()
	{
		SnakeNode* new_node = new SnakeNode();
		SnakeNode* current = snake.head;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		new_node->direction = current->direction;

		switch (new_node->direction)
		{
		case SD_DOWN:
			new_node->position = Position(current->position.x, current->position.y - 1);
			break;
		case SD_UP:
			new_node->position = Position(current->position.x, current->position.y + 1);
			break;
		case SD_LEFT:
			new_node->position = Position(current->position.x + 1, current->position.y);
			break;
		case SD_RIGHT:
			new_node->position = Position(current->position.x - 1, current->position.y);
			break;
		}

		current->next = new_node;
		new_node->next = nullptr;

		snake.length++;
	}

	Position TransportSnake(Position entrance_position)
	{
		return transport_gate_map[entrance_position];
	}

	void MoveSnake(SnakeDirection direction)
	{
		int move_x, move_y;
		int new_x, new_y;

		switch (direction)
		{
		case SD_DOWN:
			move_x = 0;
			move_y = 1;
			break;
		case SD_UP:
			move_x = 0;
			move_y = -1;
			break;
		case SD_LEFT:
			move_x = -1;
			move_y = 0;
			break;
		case SD_RIGHT:
			move_x = 1;
			move_y = 0;
			break;
		}

		SnakeNode* current = snake.head;
		new_x = current->position.x + move_x;
		new_y = current->position.y + move_y;

		/* 检查是否撞到树 */
		if (new_x < 0 || new_x >= MAP_WIDTH || new_y < 0 || new_y >= MAP_HEIGHT
			|| map_status[ML_ENVIRONMENT][new_y][new_x] == ME_ENVIRONMENT_TREE
			|| map_status[ML_ENVIRONMENT][new_y][new_x] == ME_ENVIRONMENT_TREES
			|| CheckCollisionOnSnakeBody(Position(new_x, new_y)))
		{
			game_finish = true;
			return;
		}

		/* 是否拾取到物品 */
		if (map_status[ML_ITEM][new_y][new_x] != ME_EMPTY)
		{
			PickUpItem(Position(new_x, new_y));
		}

		/* 是否接触传送门 */
		if (map_status[ML_ENVIRONMENT][new_y][new_x] == ME_ENVIRONMENT_TRANSPORT_GATE_ENTRANCE)
		{
			Position exit_position = TransportSnake(Position(new_x, new_y));
			new_x = exit_position.x;
			new_y = exit_position.y;
		}

		/* 移动蛇的身体 */
		SnakeDirection prev_direction = current->direction;
		current->direction = direction;
		int prev_x = current->position.x;
		int prev_y = current->position.y;
		current->position.x = new_x;
		current->position.y = new_y;
		current = current->next;
		while (current != nullptr)
		{
			SnakeDirection temp_direction = current->direction;
			current->direction = prev_direction;
			int temp_x = current->position.x;
			int temp_y = current->position.y;
			current->position.x = prev_x;
			current->position.y = prev_y;
			prev_direction = temp_direction;
			prev_x = temp_x;
			prev_y = temp_y;
			current = current->next;
		}
	}

	bool CheckGameFinish()
	{
		return game_finish;
	}

	void Release()
	{
		SnakeNode* current = snake.head;
		while (current != nullptr)
		{
			SnakeNode* temp = current;
			current = current->next;
			delete temp;
		}
	}

	void GameLoop()
	{
		bool is_to_turn = false;
		SnakeDirection to_turn_direction;

		srand(static_cast<unsigned>(time(nullptr)));

		static unsigned tick_snake_move = clock();
		static unsigned tick_item_generate = clock();

		while (!CheckGameFinish())
		{
			DrawGame();

			if (clock() - tick_snake_move >= REFRESH_TERMINAL / snake.velocity)
			{
				if (is_to_turn)
				{
					if (!(snake.head->direction == SD_UP && to_turn_direction == SD_DOWN
						|| snake.head->direction == SD_DOWN && to_turn_direction == SD_UP
						|| snake.head->direction == SD_LEFT && to_turn_direction == SD_RIGHT
						|| snake.head->direction == SD_RIGHT && to_turn_direction == SD_LEFT))
					{
						snake.head->direction = to_turn_direction;
					}
					is_to_turn = false;
				}
				MoveSnake(snake.head->direction);
				tick_snake_move = clock();
			}

			if (clock() - tick_item_generate >= item_generate_terminal)
			{
				GenerateItem(static_cast<ItemEnum>(rand() % 2 + 1));

				DrawGame();

				tick_item_generate = clock();
			}

			if (_kbhit())
			{
				int key = _getch();
				switch (key)
				{
				case 'w':
				case 'W':
						is_to_turn = true;
						to_turn_direction = SD_UP;
					break;
				case 's':
				case 'S':
						is_to_turn = true;
						to_turn_direction = SD_DOWN;
					break;
				case 'a':
				case 'A':
						is_to_turn = true;
						to_turn_direction = SD_LEFT;
					break;
				case 'd':
				case 'D':
						is_to_turn = true;
						to_turn_direction = SD_RIGHT;
					break;
				}
			}
		}

		DrawGame();
	}

	void GluttonousSnake()
	{
		initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);

		LoadAssets();
		InitGameStatus();

		GameLoop();

		_getch();
		closegraph();
	}
}
