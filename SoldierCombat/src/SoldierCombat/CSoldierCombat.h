#pragma once

#include <iostream>

#include <conio.h>
#include <graphics.h>
#include <Utils/Utils.h>

#include "src/Soldier/CActor.h"
#include "src/Soldier/CSoldier.h"

class CSoldierCombatV2
{
public:
	static constexpr int SCALE = 1;
	static constexpr float TERMINAL = 500.0f;

	static constexpr int GRAPH_WIDTH = 960;
	static constexpr int GRAPH_HEIGHT = 540;

	const std::wstring IMG_PATH_BG = L"assets/imgs/ui/ui_background.jpg";
	const std::wstring IMG_PATH_ARCHER = L"assets/imgs/soldiers/archer.png";
	const std::wstring IMG_PATH_LANCER = L"assets/imgs/soldiers/lancer.png";
	const std::wstring IMG_PATH_HEAVY_ARMORED = L"assets/imgs/soldiers/heavy_armored.png";

GET_SET_FUN_DECLAR(IMAGE, m_bg_img, BgImg)

public:

	CSoldierCombatV2();

	~CSoldierCombatV2();

	void DrawBackground(const std::wstring& img_path, const int scale);

	void DrawGameFinish();

	CSoldier* CreateSoldier(const CActor::Position& position);

	void GameLoop();

	void RunGame();
};
