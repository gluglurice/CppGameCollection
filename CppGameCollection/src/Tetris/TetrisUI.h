#pragma once

#include <string>

#include <graphics.h>

#include "../Utils.h"

namespace tetris
{
	/* UI size */
	const int TIP_BAR_WIDTH = 200;

	/* UI assets */
	const int UI_IMG_NUM = 6;
	const std::wstring ui_img_paths[] = {
		L"assets/Tetris/imgs/ui/ui_background.png",
		L"assets/Tetris/imgs/ui/keyboard_w.png",
		L"assets/Tetris/imgs/ui/keyboard_a.png",
		L"assets/Tetris/imgs/ui/keyboard_s.png",
		L"assets/Tetris/imgs/ui/keyboard_d.png",
		L"assets/Tetris/imgs/ui/keyboard_space.png",
	};
	enum UIImg
	{
		UII_BACKGROUND,
		UII_KEYBOARD_W,
		UII_KEYBOARD_A,
		UII_KEYBOARD_S,
		UII_KEYBOARD_D,
		UII_KEYBOARD_SPACE,
	};
	extern IMAGE ui_imgs[UI_IMG_NUM];
}
