#include "CSoldierCombatV2.h"

#include "src/Soldier/CActor.h"
#include "src/Soldier/CSoldier.h"
#include "src/Soldier/CArcher.h"
#include "src/Soldier/CLancer.h"
#include "src/Soldier/CHeavyArmored.h"

CSoldierCombatV2::CSoldierCombatV2() {}

CSoldierCombatV2::~CSoldierCombatV2() {}

void CSoldierCombatV2::DrawBackground(const std::wstring& img_path, const int scale)
{
	loadimage(&m_bg_img, img_path.c_str());
	putimage_alpha_zoom(0, 0, scale, &m_bg_img);
}

void CSoldierCombatV2::DrawGameFinish()
{
	settextcolor(WHITE);
	settextstyle(100, 0, L"Arial");

	if (heros_alive <= 0)
	{
		outtextxy(200, GRAPH_HEIGHT / 2 - 50, L"你输了！");
	}
	else
	{
		outtextxy(200, GRAPH_HEIGHT / 2 - 50, L"你赢了！");
	}
}

CSoldier* CSoldierCombatV2::CreateSoldier(CSoldier::SoldierType type, const CActor::Position& position)
{
	if (type == CSoldier::ARCHER)
	{
		return new CArcher(position, IMG_PATH_ARCHER);
	}
	else if (type == CSoldier::LANCER)
	{
		return new CLancer(position, IMG_PATH_LANCER);
	}
	else
	{
		return new CHeavyArmored(position, IMG_PATH_HEAVY_ARMORED);
	}
}

CSoldier* CSoldierCombatV2::CreateSoldier(const CActor::Position& position)
{
	CSoldier::SoldierType type = (CSoldier::SoldierType)(rand() % 3);

	if (type == CSoldier::ARCHER)
	{
		return new CArcher(position, IMG_PATH_ARCHER);
	}
	else if (type == CSoldier::LANCER)
	{
		return new CLancer(position, IMG_PATH_LANCER);
	}
	else
	{
		return new CHeavyArmored(position, IMG_PATH_HEAVY_ARMORED);
	}
}

void CSoldierCombatV2::GameLoop()
{
	/* 选英雄 */

	DrawBackground(IMG_PATH_BG, SCALE);

	CActor::Position hero_pos[HERO_NUM] = {
		{ 50, 10 },
		{ 200, 170 },
		{ 50, 330 },
	};

	CActor::Position enemy_pos[ENEMY_NUM] = {
		{ 700, 10 },
		{ 550, 170 },
		{ 700, 330 }
	};

	CSoldier* heros[HERO_NUM];
	outtextxy(200, GRAPH_HEIGHT / 2 - 25, L"请选择你的3个英雄（0：弓箭手，1：枪兵，2：重甲兵）（使用空格隔开数字即可）：");

	int chosen_types[HERO_NUM];
	for (int i = 0; i < HERO_NUM; i++)
	{
		std::cin >> chosen_types[i];
		heros[i] = CreateSoldier((CSoldier::SoldierType)chosen_types[i], hero_pos[i]);
	}

	CSoldier* enemies[ENEMY_NUM];
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemies[i] = CreateSoldier(enemy_pos[i]);
	}

	DrawBackground(IMG_PATH_BG, SCALE);

	for (int i = 0; i < HERO_NUM; i++)
	{
		heros[i]->Draw(SCALE);
	}

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemies[i]->Draw(SCALE);
	}

	/* 战斗 */

	while (heros_alive > 0 && enemies_alive > 0)
	{
		/* Heros attack enemies */
		for (int i = 0; i < HERO_NUM; i++)
		{
			if (heros[i]->GetHP() > 0)
			{
				int target_id = rand() % ENEMY_NUM;
				while (true)
				{
					if (enemies[target_id]->GetHP() > 0) {
						break;
					}
					target_id = rand() % ENEMY_NUM;
				}
				heros[i]->Attack(enemies, target_id, ENEMY_NUM);

				if (enemies[target_id]->GetHP() <= 0)
				{
					enemies_alive--;
				}
				enemies[target_id]->Draw(SCALE);

				if (enemies_alive <= 0)
				{
					break;
				}

				Sleep(TERMINAL);
			}
		}

		/* Enemies attack heros */
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemies[i]->GetHP() > 0)
			{
				int target_id = rand() % HERO_NUM;
				while (true)
				{
					if (heros[target_id]->GetHP() > 0) {
						break;
					}
					target_id = rand() % HERO_NUM;
				}
				enemies[i]->Attack(heros, target_id, HERO_NUM);

				if (heros[target_id]->GetHP() <= 0)
				{
					heros_alive--;
				}
				heros[target_id]->Draw(SCALE);

				if (heros_alive <= 0)
				{
					break;
				}

				Sleep(TERMINAL);
			}
		}
	}

	DrawGameFinish();

	for (int i = 0; i < HERO_NUM; i++)
	{
		delete heros[i];
	}

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		delete enemies[i];
	}
}

void CSoldierCombatV2::RunGame()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);

	GameLoop();

	_getch();
	closegraph();
}

GET_SET_FUN_DEFINE(IMAGE, CSoldierCombatV2, m_bg_img, BgImg)
