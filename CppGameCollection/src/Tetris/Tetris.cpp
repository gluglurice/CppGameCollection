#include "Tetris.h"

namespace tetris
{
	bool should_generate_cube = true;
	int score = 0;
	Cube current_cube;
	Cube next_cube;
	bool game_finish = false;

	void LoadMapAssets()
	{
		/* Load map images */
		for (int i = 0; i < MAP_IMG_NUM; i++)
		{
			loadimage(&map_imgs[i], map_img_paths[i].c_str());
		}

		/* Load map original status data */
		for (int row = 0; row < MAP_HEIGHT; row++)
		{
			for (int col = 0; col < MAP_WIDTH; col++)
			{
				map_status_original[ML_TERRAIN][row][col] = (row == WALL_ROW_INDEX || row == MAP_HEIGHT - 1 || col == 0 || col == MAP_WIDTH - 1);
			}
		}
		for (int row = 0; row < MAP_HEIGHT; row++)
		{
			for (int col = 0; col < MAP_WIDTH; col++)
			{
				map_status_original[ML_CUBE][row][col] = 0;
			}
		}
	}

	void LoadCubeAssets()
	{
		/* Load cube images */
		for (int i = 0; i < CUBE_IMG_NUM; i++)
		{
			loadimage(&cube_imgs[i], cube_img_paths[i].c_str());
		}
	}

	void LoadUIAssets()
	{
		/* Load UI images */
		for (int i = 0; i < UI_IMG_NUM; i++)
		{
			loadimage(&ui_imgs[i], ui_img_paths[i].c_str());
		}
	}

	void LoadAssets()
	{
		LoadMapAssets();
		LoadCubeAssets();
		LoadUIAssets();
	}

	void InitGameStatus()
	{
		srand(static_cast<unsigned>(time(nullptr)));

		/* Initialize map status */
		memcpy(map_status, map_status_original, sizeof map_status_original);

		/* Initialize the next cube */
		CubeEnum cube_type = static_cast<CubeEnum>(rand() % CUBE_TYPE_NUM + 1);
		next_cube = Cube(cube_type, MAP_WIDTH / 2 - 1, 0);
	}

	void  DrawUI()
	{
		/* Set font */
		setbkmode(TRANSPARENT);
		settextcolor(RGB(0x6D, 0x4B, 0x27));
		settextstyle(20, 0, _T("微软雅黑"), 0, 0, FW_BOLD, FALSE, FALSE, FALSE);

		/* Draw UI background */
		putimage_alpha_zoom(
			MAP_WIDTH * TILE_SIZE * MAP_SCALE,
			0,
			1,
			&ui_imgs[UII_BACKGROUND]
		);

		/* Draw next cube hint */
		settextcolor(RGB(0x36, 0x40, 0x4A));

		const int UI_CUBE_SIZE = 28;
		putimage_alpha_zoom(
			MAP_WIDTH * TILE_SIZE * MAP_SCALE + 20,
			20,
			1,
			&ui_imgs[UII_NEXT_CUBE]
		);
		for (int row = 0; row < CUBE_MATRIX_SIZE; row++)
		{
			for (int col = 0; col < CUBE_MATRIX_SIZE; col++)
			{
				if (next_cube.matrix[row][col] == 1)
				{
					putimage_alpha_zoom(
						MAP_WIDTH * TILE_SIZE * MAP_SCALE + 46 + col * UI_CUBE_SIZE * MAP_SCALE,
						20 + 24 + row * UI_CUBE_SIZE * MAP_SCALE,
						UI_CUBE_SIZE * MAP_SCALE,
						UI_CUBE_SIZE * MAP_SCALE,
						&cube_imgs[next_cube.type - 1]
					);
				}
			}
		}
		outtextxy(
			MAP_WIDTH * TILE_SIZE* MAP_SCALE + 60,
			190,
			_T("Next cube")
		);

		/* Draw score */
		putimage_alpha_zoom(
			MAP_WIDTH * TILE_SIZE * MAP_SCALE + 20,
			230,
			1,
			&ui_imgs[UII_SCORE]
		);
		outtextxy(
			MAP_WIDTH * TILE_SIZE * MAP_SCALE + 80,
			230 + 26,
			_T("Score")
		);
		std::wstring score_str = std::to_wstring(score);
		int score_str_len = score_str.length();
		for (int i = 0; i < SCORE_STR_LEN - score_str_len; i++)
		{
			score_str.insert(i, L"0");
		}
		outtextxy(
			MAP_WIDTH * TILE_SIZE * MAP_SCALE + 66,
			230 + 26 + 20,
			score_str.c_str()
		);

		/* Draw UI keys */
		const int UI_KEY_WIDTH_MID = 130;
		const int UI_KEY_SIZE = 48;
		const int UI_KEY_SCALE = 2;
		const float UI_KEY_HEIGHT_FACTOR = 0.6f;

		settextcolor(RGB(0x6D, 0x4B, 0x27));
		putimage_alpha_zoom(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			&ui_imgs[UII_KEYBOARD_W]
		);
		outtextxy(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID + 8,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR + 64,
			_T("Rotate")
		);

		putimage_alpha_zoom(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE * UI_KEY_SCALE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			&ui_imgs[UII_KEYBOARD_S]
		);
		putimage_alpha_zoom(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID - UI_KEY_SIZE,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE * UI_KEY_SCALE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			&ui_imgs[UII_KEYBOARD_A]
		);
		putimage_alpha_zoom(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID + UI_KEY_SIZE,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE * UI_KEY_SCALE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			TILE_SIZE * MAP_SCALE * UI_KEY_SCALE,
			&ui_imgs[UII_KEYBOARD_D]
		);

		outtextxy(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID + 10,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE * UI_KEY_SCALE + 64,
			_T("Move")
		);

		putimage_alpha_zoom(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID - UI_KEY_SIZE - 8,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE * UI_KEY_SCALE * 2,
			MAP_SCALE * UI_KEY_SCALE,
			&ui_imgs[UII_KEYBOARD_SPACE]
		);
		outtextxy(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID + 12,
			GRAPH_HEIGHT * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE * UI_KEY_SCALE * 2 + 64,
			_T("Drop")
		);
	}

	void DrawMap()
	{
		for (int layer = 0; layer < MAP_LAYER_NUM - 1; layer++)
		{
			for (int row = WALL_ROW_INDEX; row < MAP_HEIGHT; row++)
			{
				for (int col = 0; col < MAP_WIDTH; col++)
				{
					putimage_alpha_zoom(
						col * TILE_SIZE * MAP_SCALE,
						(row - WALL_ROW_INDEX) * TILE_SIZE * MAP_SCALE,
						TILE_SIZE * MAP_SCALE,
						TILE_SIZE * MAP_SCALE,
						&map_imgs[map_status[layer][row][col]]
					);
				}
			}
		}
	}

	void DrawCube()
	{
		for (int row = WALL_ROW_INDEX + 1; row < MAP_HEIGHT - 1; row++)
		{
			for (int col = 1; col < MAP_WIDTH - 1; col++)
			{
				if (map_status[ML_CUBE][row][col] != CE_EMPTY)
				{
					putimage_alpha_zoom(
						col * TILE_SIZE * MAP_SCALE,
						(row - WALL_ROW_INDEX) * TILE_SIZE * MAP_SCALE,
						TILE_SIZE * MAP_SCALE,
						TILE_SIZE * MAP_SCALE,
						&cube_imgs[map_status[ML_CUBE][row][col] - 1]
					);
				}
			}
		}
	}

	void DrawGameFinishUI()
	{
		const int UI_TIPS_WIDTH_LEFT = 172;
		const float UI_TIPS_HEIGHT_FACTOR = 0.45f;

		setbkcolor(RGB(0xFF, 0xF1, 0xD2));
		setbkmode(OPAQUE);
		settextcolor(RGB(0x6D, 0x4B, 0x27));
		settextstyle(20, 0, _T("微软雅黑"), 0, 0, FW_BOLD, FALSE, FALSE, FALSE);
		outtextxy(
			GRAPH_WIDTH - UI_TIPS_WIDTH_LEFT,
			GRAPH_HEIGHT * UI_TIPS_HEIGHT_FACTOR,
			_T("The container is full.")
		);
	}

	void DrawGame()
	{
		BeginBatchDraw();
		DrawUI();
		DrawMap();
		DrawCube();
		if (game_finish)
		{
			DrawGameFinishUI();
		}
		FlushBatchDraw();
	}

	void PrintCubeOnMap(Cube cube, PrintModeEnum mode)
	{
		for (int i = 0; i < CUBE_MATRIX_SIZE; i++)
		{
			for (int j = 0; j < CUBE_MATRIX_SIZE; j++)
			{
				if (cube.matrix[i][j] == 1)
				{
					map_status[ML_CUBE][cube.position.y + i][cube.position.x + j] = mode == PME_PRINT ? cube.type : CE_EMPTY;
				}
			}
		}
	}

	void GenerateCube()
	{
		current_cube = next_cube;
		PrintCubeOnMap(current_cube, PME_PRINT);

		CubeEnum cube_type = static_cast<CubeEnum>(rand() % CUBE_TYPE_NUM + 1);
		next_cube = Cube(cube_type, MAP_WIDTH / 2 - 1, 0);
	}

	bool CheckCubeCollision(int new_x, int new_y, int matrix[][CUBE_MATRIX_SIZE])
	{
		for (int i = 0; i < CUBE_MATRIX_SIZE; i++)
		{
			for (int j = 0; j < CUBE_MATRIX_SIZE; j++)
			{
				if ((new_x + j <= 0
					|| new_x + j >= MAP_WIDTH - 1
					|| new_y + i >= MAP_HEIGHT - 1
					|| map_status[ML_CUBE][new_y + i][new_x + j] != CE_EMPTY)
					&& matrix[i][j])
				{
					return true;
				}
			}
		}
		return false;
	}

	void CheckAndEraseCube()
	{
		int top = WALL_ROW_INDEX;
		int row = MAP_HEIGHT - 2;
		int erase_row = -1;

		while (row > top)
		{
			bool should_erase = true;

			for (int col = 1; col < MAP_WIDTH - 1; col++)
			{
				if (map_status[ML_CUBE][row][col] == CE_EMPTY)
				{
					should_erase = false;
					break;
				}
				erase_row = row;
			}
			if (should_erase)
			{
				score += SCORE_PER_LINE;
				for (int i = erase_row; i > top; i--)
				{
					for (int j = 1; j < MAP_WIDTH - 1; j++)
					{
						map_status[ML_CUBE][i][j] = map_status[ML_CUBE][i - 1][j];
					}
				}
				top--;
				continue;
			}
			row--;
		}
	}

	void MoveCube(int move_x, int move_y)
	{
		int new_x = current_cube.position.x + move_x;
		int new_y = current_cube.position.y + move_y;

		PrintCubeOnMap(current_cube, PME_ERASE);

		if (CheckCubeCollision(new_x, new_y, current_cube.matrix))
		{
			if (move_y == 1)
			{
				PrintCubeOnMap(current_cube, PME_PRINT);

				CheckAndEraseCube();

				if (CheckGameFinish())
				{
					return;
				}

				GenerateCube();
				should_generate_cube = false;
				return;
			}
		}
		else
		{
			current_cube.position.x = new_x;
			current_cube.position.y = new_y;
		}

		PrintCubeOnMap(current_cube, PME_PRINT);
	}

	void DropCube()
	{
		PrintCubeOnMap(current_cube, PME_ERASE);

		int new_y = current_cube.position.y;
		while (!CheckCubeCollision(current_cube.position.x, new_y + 1, current_cube.matrix))
		{
			new_y++;
		}
		current_cube.position.y = new_y;

		PrintCubeOnMap(current_cube, PME_PRINT);
	}

	void RotateCube()
	{
		int tmp_matrix[CUBE_MATRIX_SIZE][CUBE_MATRIX_SIZE] = { 0 };

		switch (current_cube.type)
		{
		case CE_O:
			return;
		
		case CE_I:
			PrintCubeOnMap(current_cube, PME_ERASE);
			for (int i = 0; i < CUBE_MATRIX_SIZE; i++)
			{
				for (int j = 0; j < CUBE_MATRIX_SIZE; j++)
				{
					tmp_matrix[i][j] = current_cube.matrix[CUBE_MATRIX_SIZE - 1 - j][CUBE_MATRIX_SIZE - 1 - i];
				}
			}
			break;
		
		default:
			PrintCubeOnMap(current_cube, PME_ERASE);
			for (int i = 1; i < CUBE_MATRIX_SIZE; i++)
			{
				for (int j = 0; j < CUBE_MATRIX_SIZE - 1; j++)
				{
					tmp_matrix[i][j] = current_cube.matrix[3 - j][i - 1];
				}
			}
			break;
		}

		if (!CheckCubeCollision(current_cube.position.x, current_cube.position.y, tmp_matrix))
		{
			for (int i = 0; i < CUBE_MATRIX_SIZE; i++)
			{
				for (int j = 0; j < CUBE_MATRIX_SIZE; j++)
				{
					current_cube.matrix[i][j] = tmp_matrix[i][j];
				}
			}
		}
		PrintCubeOnMap(current_cube, PME_PRINT);
	}

	bool CheckGameFinish()
	{
		for (int i = 0; i < CUBE_MATRIX_SIZE; i++)
		{
			for (int j = 0; j < CUBE_MATRIX_SIZE; j++)
			{
				if (current_cube.matrix[i][j] == 1 && current_cube.position.y + i <= WALL_ROW_INDEX)
				{
					game_finish = true;
					return game_finish;
				}
			}
		}
		return game_finish;
	}

	void GameLoop()
	{
		static unsigned tick_cube_move = clock();

		while (!game_finish)
		{
			DrawGame();

			if (should_generate_cube)
			{
				GenerateCube();
				should_generate_cube = false;
			}

			if (clock() - tick_cube_move >= REFRESH_TERMINAL)
			{
				MoveCube(0, 1);
				tick_cube_move = clock();
			}

			if (_kbhit())
			{
				int key = _getch();
				switch (key)
				{
				case 'w':
				case 'W':
					RotateCube();
					break;
				case 's':
				case 'S':
					MoveCube(0, 1);
					break;
				case 'a':
				case 'A':
					MoveCube(-1, 0);
					break;
				case 'd':
				case 'D':
					MoveCube(1, 0);
					break;
				case ' ':
					DropCube();
					break;
				}
			}
		}

		DrawGame();
	}

	void Tetris()
	{
		initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);

		LoadAssets();
		InitGameStatus();

		GameLoop();

		_getch();
		closegraph();
	}
}
