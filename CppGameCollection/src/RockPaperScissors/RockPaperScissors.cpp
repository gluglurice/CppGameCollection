#include "RockPaperScissors.h"

namespace rock_paper_scissors
{

	static int coin = 3;

	void Gameplay(int& coin)
	{
		while (coin > 0)
		{
			std::cout << "欢迎来到猜拳游戏！" << std::endl;
			std::cout << "你现在有 " << coin << " 个硬币（硬币归零，游戏结束）" << std::endl;
			std::cout << "请输入一个数字（1：石头，2：剪刀，3：布）：" << std::endl;

			int pc = _getch() - '0';

			if (pc < 1 || pc > 3)
			{
				std::cout << "无效输入，请重新输入！" << std::endl;
				system("pause");
				system("cls");
				continue;
			}

			int cpu = rand() % 3 + 1;
			int res = pc - cpu;

			std::cout << "你出的是：" << (pc == 1 ? "石头" : pc == 2 ? "剪刀" : "布") << std::endl;
			std::cout << "电脑出的是：" << (cpu == 1 ? "石头" : cpu == 2 ? "剪刀" : "布") << std::endl;

			if (res == 0)
			{
				std::cout << "平局！" << std::endl;
			}
			else if (res == -1 || res == 2)
			{
				std::cout << "你赢了！奖励 1 个硬币" << std::endl;
				coin++;
			}
			else
			{
				std::cout << "你输了！扣除 1 个硬币" << std::endl;
				coin--;
			}

			system("pause");
			system("cls");

			if (coin <= 0)
			{
				bool isContinueGame = false;
				while (true)
				{
					std::cout << "你的硬币已经用完！是否需要充值？（0：退出游戏，1：继续游戏，2：充值 5 个硬币，3：充值 10 个硬币， 4：充值 20 个硬币）" << std::endl;
					int choice = _getch() - '0';
					switch (choice)
					{
					case 0:
						std::cout << "感谢游戏！再见！" << std::endl;
						return;
					case 1:
						if (coin <= 0)
						{
							std::cout << "你的硬币已经用完！请充值后再继续游戏！" << std::endl;
							continue;
						}
						else
						{
							isContinueGame = true;
							break;
						}
					case 2:
						coin += 5;
						std::cout << "充值成功！你现在有 " << coin << " 个硬币。" << std::endl;
						continue;
					case 3:
						coin += 10;
						std::cout << "充值成功！你现在有 " << coin << " 个硬币。" << std::endl;
						continue;
					case 4:
						coin += 20;
						std::cout << "充值成功！你现在有 " << coin << " 个硬币。" << std::endl;
						continue;
					default:
						std::cout << "无效选择，请重新输入！" << std::endl;
						continue;
					}
					if (isContinueGame)
					{
						break;
					}
				}
			}
		}
	}

	void RockPaperScissors()
	{
		srand(time(0));

		Gameplay(coin);

		system("pause");
	}

}
