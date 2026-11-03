#include "DrawDiamond.h"

namespace draw_diamond
{
	void DrawDiamond()
	{
		int size = 5;
		int col = size * 2 - 1;
		int row = size * 2 - 1;
		std::string edge = "★";

		// 绘制空心菱形上半
		for (int i = 0; i < row / 2 + 1; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (j == col / 2 + i || j == col / 2 - i)
				{
					std::cout << edge;
				}
				else
				{
					std::cout << " ";
				}
			}
			std::cout << std::endl;
		}

		// 绘制空心菱形下半
		for (int i = row / 2 + 1; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (j == col / 2 + (row - i - 1) || j == col / 2 - (row - i - 1))
				{
					std::cout << edge;
				}
				else
				{
					std::cout << " ";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		system("pause");
	}

}
