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

void CSoldierCombat::GameLoop()
{
	CActor::Position pos_left = { 100, 170 };
	CActor::Position pos_right = { 700, 170 };

	CSoldier archer = CArcher(pos_left, L"assets/imgs/soldiers/archer.png");
	archer.Draw(1);

	CSoldier lancer = CLancer(pos_right, L"assets/imgs/soldiers/lancer.png");
	lancer.Draw(1);
}

void CSoldierCombat::RunGame()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	initgraph(960, 540);

	DrawBackground(L"assets/imgs/ui/ui_background.jpg", 1);
	GameLoop();

	_getch();
	closegraph();
}

GET_SET_FUN_DEFINE(IMAGE, CSoldierCombat, m_bg_img, BgImg)
