#pragma once

#include <string>

#include <graphics.h>

#include "src/Utils/Utils.h"
#include "GluttonousSnakeActor.h"

namespace gluttonous_snake
{
	/* 物品图片索引 */
	enum ItemEnum
	{
		IE_FOOD = 1,
		IE_GAS = 2,
	};

	/* 物品 */
	struct Item
	{
		Position position;

		Item() {}

		Item(int x, int y) : position(x, y) {}
	};

	/* 物品资产路径 */
	const int ITEM_IMG_NUM = 2;
	const std::wstring item_img_paths[] = {
		L"assets/GluttonousSnake/imgs/item/item_food.png",
		L"assets/GluttonousSnake/imgs/item/item_gas.png"
	};

	/* 物品元素图片 */
	extern IMAGE item_imgs[ITEM_IMG_NUM];
}
