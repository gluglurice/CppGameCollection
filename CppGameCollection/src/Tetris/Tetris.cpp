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
		putimage(
			MAP_WIDTH * TILE_SIZE * MAP_SCALE,
			0,
			&ui_imgs[UII_BACKGROUND]
		);

		/* Draw next cube hint */


		/* Draw UI keys */
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
		outtextxy(
			GRAPH_WIDTH - UI_KEY_WIDTH_MID + 16,
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
			GRAPH_WIDTH - UI_KEY_WIDTH_MID + 16,
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
			GRAPH_WIDTH - UI_KEY_WIDTH_MID,
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
		const int UI_TIPS_WIDTH_MID = 150;
		const float UI_TIPS_HEIGHT_FACTOR = 0.4f;

		setbkcolor(RGB(0xFF, 0xF1, 0xD2));
		setbkmode(OPAQUE);
		settextcolor(RGB(0x6D, 0x4B, 0x27));
		settextstyle(20, 0, _T("微软雅黑"), 0, 0, FW_BOLD, FALSE, FALSE, FALSE);
		outtextxy(
			GRAPH_WIDTH - UI_TIPS_WIDTH_MID,
			GRAPH_HEIGHT * UI_TIPS_HEIGHT_FACTOR,
			_T("You failed.")
		);
	}

	void DrawGame()
	{
		BeginBatchDraw();
		DrawUI();
		DrawMap();
		DrawCube();
		if (CheckGameFinish())
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

		should_generate_cube = false;
	}

	void MoveCube(int move_x, int move_y)
	{
		int new_x = current_cube.position.x + move_x;
		int new_y = current_cube.position.y + move_y;

		PrintCubeOnMap(current_cube, PME_ERASE);
		current_cube.position.x = new_x;
		current_cube.position.y = new_y;
		PrintCubeOnMap(current_cube, PME_PRINT);
	}

	void RotateCube()
	{

	}

	bool CheckShouldEraseCube()
	{
		return false;
	}

	void EraseCube()
	{

	}

	bool CheckGameFinish()
	{
		return game_finish;
	}

	void GameLoop()
	{
		static unsigned tick_cube_move = clock();

		while (!CheckGameFinish())
		{
			DrawGame();

			if (should_generate_cube)
			{
				GenerateCube();
			}

			if (clock() - tick_cube_move >= REFRESH_TERMINAL)
			{
				MoveCube(0, 1);
				tick_cube_move = clock();
			}

			if (CheckShouldEraseCube())
			{
				EraseCube();
				should_generate_cube = true;
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
