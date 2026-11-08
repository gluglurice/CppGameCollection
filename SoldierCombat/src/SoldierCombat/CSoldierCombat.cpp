#include "CSoldierCombat.h"

#include "src/Soldier/CActor.h"
#include "src/Soldier/CSoldier.h"
#include "src/Soldier/CArcher.h"
#include "src/Soldier/CLancer.h"
#include "src/Soldier/CHeavyArmored.h"

CSoldierCombat::CSoldierCombat() {}

CSoldierCombat::~CSoldierCombat() {}

void CSoldierCombat::DrawBackground(const std::wstring& img_path, const int scale)
{
	loadimage(&m_bg_img, img_path.c_str());
	putimage_alpha_zoom(0, 0, scale, &m_bg_img);
}

void CSoldierCombat::DrawGameFinish()
{
	settextcolor(WHITE);
	settextstyle(100, 0, L"Arial");

	outtextxy(150, GRAPH_HEIGHT / 2 - 25, L"Game Finished");
}

CSoldier* CSoldierCombat::CreateSoldier(const CActor::Position& position)
{
	int type = rand() % 3;

	if (type == 0)
	{
		return new CArcher(position, IMG_PATH_ARCHER);
	}
	else if (type == 1)
	{
		return new CLancer(position, IMG_PATH_LANCER);
	}
	else
	{
		return new CHeavyArmored(position, IMG_PATH_HEAVY_ARMORED);
	}
}

void CSoldierCombat::GameLoop()
{
	DrawBackground(IMG_PATH_BG, SCALE);

	CActor::Position pos_left = { 100, 170 };
	CActor::Position pos_right = { 700, 170 };

	CSoldier* soldier_left = new CLancer(pos_left, IMG_PATH_LANCER);
	//CSoldier* soldier_left = CreateSoldier(pos_left);
	CSoldier* soldier_right = CreateSoldier(pos_right);

	soldier_left->Draw(SCALE);
	soldier_right->Draw(SCALE);

	while (soldier_left->GetHP() > 0 && soldier_right->GetHP() > 0)
	{
		soldier_left->Attack(*soldier_right);
		soldier_right->Draw(SCALE);
		if (soldier_right->GetHP() <= 0)
		{
			break;
		}
		Sleep(TERMINAL);

		soldier_right->Attack(*soldier_left);
		soldier_left->Draw(SCALE);
		Sleep(TERMINAL);
	}

	DrawGameFinish();

	delete soldier_left;
	delete soldier_right;
}

void CSoldierCombat::RunGame()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);

	GameLoop();

	_getch();
	closegraph();
}

GET_SET_FUN_DEFINE(IMAGE, CSoldierCombat, m_bg_img, BgImg)
