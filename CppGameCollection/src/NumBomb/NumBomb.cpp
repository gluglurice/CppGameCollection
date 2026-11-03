#include "NumBomb.h"

namespace num_bomb
{

	void NumBomb()
	{
		srand(time(0));
		int bomb = rand() % 1000 + 1;
		int chance = 8;
		bool success = false;

		std::cout << "欢迎来到拆弹游戏！" << std::endl;
		std::cout << "你有 " << chance << " 次机会来拆除炸弹。" << std::endl;

		while (chance > 0)
		{
			int guess;
			std::cout << "请输入你猜测的炸弹编号（1-1000）：";
			std::cin >> guess;
			if (guess < 1 || guess > 1000)
			{
				std::cout << "输入无效，请输入一个介于 1 和 1000 之间的数字。" << std::endl;
				continue;
			}
			if (guess == bomb)
			{
				std::cout << "恭喜你！你成功拆除了炸弹！" << std::endl;
				success = true;
				return;
			}
			else if (guess < bomb)
			{
				std::cout << "炸弹编号更大，请再试一次。" << std::endl;
			}
			else
			{
				std::cout << "炸弹编号更小，请再试一次。" << std::endl;
			}
			chance--;
			std::cout << "你还有 " << chance << " 次机会。" << std::endl;
		}
		if (!success)
		{
			std::cout << "很遗憾，你没有在规定次数内拆除炸弹。" << std::endl;
		}
		system("pause");
	}

}
