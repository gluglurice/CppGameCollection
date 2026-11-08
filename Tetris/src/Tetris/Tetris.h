#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include <string>

#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <Utils/Utils.h>

#include "TetrisMap.h"
#include "TetrisCube.h"
#include "TetrisUI.h"

namespace tetris
{
	/* Global Variables */
	const float REFRESH_TERMINAL = 500.0f;
	const int SCORE_PER_LINE = 10;
	const int SCORE_STR_LEN = 8;

	extern int score;
	extern bool should_generate_cube;
	extern Cube current_cube;
	extern Cube next_cube;
	extern bool game_finish;

	enum PrintModeEnum
	{
		PME_ERASE,
		PME_PRINT,
	};

	/* Load Assets */

	void LoadMapAssets();

	void LoadCubeAssets();

	void LoadUIAssets();

	void LoadAssets();

	/* Init Game */

	void InitGameStatus();

	/* Drawing */

	void DrawUI();

	void DrawMap();

	void DrawCube();

	void DrawGameFinishUI();

	void DrawGame();

	/* Game Logic */

	/**
	 * @brief Print or erase current cube on map
	 * @param cube 
	 * @param mode
	 */
	void PrintCubeOnMap(Cube cube, PrintModeEnum mode);

	void GenerateCube();

	bool CheckCubeCollision(int new_x, int new_y);

	void CheckAndEraseCube();

	void MoveCube();

	void DropCube();

	void RotateCube();

	bool CheckGameFinish();

	void GameLoop();

	/* Main Function */

	void Tetris();
}
