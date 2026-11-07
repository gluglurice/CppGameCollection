#include "Gacha.h"

namespace gacha
{
	/****************** 常量 ******************/
	const int GRAPH_WIDTH = 600;
	const int GRAPH_HEIGHT = 640;
	const int IMG_NUM = 10;
	const int IMG_PATH_LENGTH = 50;
	const int REFRESH_TERMINAL = 5;

	/****************** 是否触发抽卡 ******************/
	bool choose = false;

	/****************** 当前图片序号 ******************/
	int img_chosen = 0;

	/****************** 图片资产路径 ******************/
	wchar_t img_paths[IMG_NUM][IMG_PATH_LENGTH] =
	{
		L"assets/Gacha/Columbina.png",
		L"assets/Gacha/Linnea.png",
		L"assets/Gacha/Mitya.png",
		L"assets/Gacha/Nicole.png",
		L"assets/Gacha/Odette.png",
		L"assets/Gacha/Sandrone.png",
		L"assets/Gacha/Varka.png",
		L"assets/Gacha/Vesna.png",
		L"assets/Gacha/Vodyanitsa.png",
		L"assets/Gacha/ZiBai.png",
	};

	/****************** 图片资产 ******************/
	IMAGE imgs[IMG_NUM];

	/**
	 * @brief 加载资产
	 */
	void LoadAssets() {
		for (int i = 0; i < IMG_NUM; i++)
		{
			loadimage(&imgs[i], img_paths[i]);
		}
	}

	/**
	 * @brief 绘制地图
	 */
	void DrawMap()
	{
		putimage_alpha(0, 0, &imgs[img_chosen]);
		outtextxy(GRAPH_WIDTH / 2 - 50, GRAPH_HEIGHT - 30, L"抽卡：空格");
	}

	/**
	 * @brief 游戏循环
	 */
	void GameLoop()
	{

		srand(time(0));

		while (true)
		{
			DrawMap();

			Sleep(REFRESH_TERMINAL);

			if (!choose)
			{
				img_chosen = rand() % IMG_NUM;
			}

			if (_kbhit())
			{
				char key = _getch();
				switch (key)
				{
				case ' ':
					choose = !choose;
					DrawMap();
					break;
				}
			}
		}
	}

	void Gacha()
	{
		initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);

		LoadAssets();

		GameLoop();

		closegraph();
	}

}