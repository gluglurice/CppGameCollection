#pragma once

#include <string>

#include <graphics.h>
#include <Utils/Utils.h>

namespace tetris
{
	const int CUBE_TYPE_NUM = 8;
	const int CUBE_MATRIX_SIZE = 4;

	struct Position
	{
		int x;
		int y;
		Position() {}
		Position(int x, int y) : x(x), y(y) {}

		bool operator<(const Position& other) const
		{
			if (x != other.x)
			{
				return x < other.x;
			}
			return y < other.y;
		}
	};

	enum CubeEnum
	{
		CE_EMPTY,
		CE_O,
		CE_T,
		CE_L,
		CE_J,
		CE_S,
		CE_Z,
		CE_I,
		CE_U,
	};

	struct Cube
	{
		CubeEnum type;
		Position position;
		int matrix[CUBE_MATRIX_SIZE][CUBE_MATRIX_SIZE] = { 0 };

		Cube() {}
		Cube(CubeEnum type, int x, int y) : type(type), position(x, y) 
		{
			switch (type)
			{
			case CE_O:
				matrix[2][1] = 1;
				matrix[2][2] = 1;
				matrix[3][1] = 1;
				matrix[3][2] = 1;
				break;
			case CE_T:
				matrix[2][1] = 1;
				matrix[3][0] = 1;
				matrix[3][1] = 1;
				matrix[3][2] = 1;
				break;
			case CE_L:
				matrix[1][1] = 1;
				matrix[2][1] = 1;
				matrix[3][1] = 1;
				matrix[3][2] = 1;
				break;
			case CE_J:
				matrix[1][1] = 1;
				matrix[2][1] = 1;
				matrix[3][1] = 1;
				matrix[3][0] = 1;
				break;
			case CE_S:
				matrix[2][1] = 1;
				matrix[2][2] = 1;
				matrix[3][0] = 1;
				matrix[3][1] = 1;
				break;
			case CE_Z:
				matrix[2][0] = 1;
				matrix[2][1] = 1;
				matrix[3][1] = 1;
				matrix[3][2] = 1;
				break;
			case CE_I:
				matrix[2][0] = 1;
				matrix[2][1] = 1;
				matrix[2][2] = 1;
				matrix[2][3] = 1;
				break;
			case CE_U:
				matrix[1][0] = 1;
				matrix[1][2] = 1;
				matrix[2][0] = 1;
				matrix[2][1] = 1;
				matrix[2][2] = 1;
				break;
			}
		}
	};

	/* Cube assets */
	const int CUBE_IMG_NUM = 8;
	const std::wstring cube_img_paths[] = {
		L"assets/Tetris/imgs/cube/cell_red.png",
		L"assets/Tetris/imgs/cube/cell_orange.png",
		L"assets/Tetris/imgs/cube/cell_yellow.png",
		L"assets/Tetris/imgs/cube/cell_brown.png",
		L"assets/Tetris/imgs/cube/cell_green.png",
		L"assets/Tetris/imgs/cube/cell_cyan.png",
		L"assets/Tetris/imgs/cube/cell_blue.png",
		L"assets/Tetris/imgs/cube/cell_purple.png",
	};
	extern IMAGE cube_imgs[CUBE_IMG_NUM];
}
