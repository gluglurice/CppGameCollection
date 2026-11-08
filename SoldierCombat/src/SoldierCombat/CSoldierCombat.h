#pragma once

#include <iostream>

#include <conio.h>
#include <graphics.h>
#include <Utils/Utils.h>

class CSoldierCombat
{
GET_SET_FUN_DECLAR(IMAGE, m_bg_img, BgImg)

public:

	CSoldierCombat();

	~CSoldierCombat();

	void DrawBackground(const std::wstring& img_path, const int scale);

	void GameLoop();

	void RunGame();
};
