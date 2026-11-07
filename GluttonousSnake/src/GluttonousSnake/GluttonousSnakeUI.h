#pragma once

#include <string>

#include <graphics.h>

#include "src/Utils/Utils.h"

namespace gluttonous_snake
{
	/* UI大小 */
	const int TIP_BAR_WIDTH = 200;

	/* UI资产路径 */
	const int UI_IMG_NUM = 5;
	const std::wstring ui_img_paths[] = {
		L"assets/GluttonousSnake/imgs/ui/ui_background.png",
		L"assets/GluttonousSnake/imgs/ui/keyboard_w.png",
		L"assets/GluttonousSnake/imgs/ui/keyboard_a.png",
		L"assets/GluttonousSnake/imgs/ui/keyboard_s.png",
		L"assets/GluttonousSnake/imgs/ui/keyboard_d.png"
	};

	/* UI图片索引 */
	enum UIImg
	{
		UII_BACKGROUND = 0,
		UII_KEYBOARD_W = 1,
		UII_KEYBOARD_A = 2,
		UII_KEYBOARD_S = 3,
		UII_KEYBOARD_D = 4
	};

	/* UI元素图片 */
	extern IMAGE ui_imgs[UI_IMG_NUM];
}
