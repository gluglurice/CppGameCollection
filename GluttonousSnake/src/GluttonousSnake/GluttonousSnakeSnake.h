#pragma once

#include <string>

#include <graphics.h>

#include "src/Utils/Utils.h"
#include "GluttonousSnakeActor.h"

namespace gluttonous_snake
{
	/* 蛇的朝向 */
	enum SnakeDirection
	{
		SD_DOWN = 0,
		SD_LEFT = 1,
		SD_RIGHT = 2,
		SD_UP = 3,
	};

	/* 蛇的节点 */
	struct SnakeNode
	{
		Position position;
		SnakeDirection direction;
		struct SnakeNode* next;

		SnakeNode() {}
		SnakeNode(int x, int y, SnakeDirection direction) : position(x, y), direction(direction), next(nullptr) {}
	};

	/* 蛇 */
	struct Snake
	{
		int length;
		float velocity;
		SnakeNode* head;

		Snake() {}

		Snake(int length, float velocity, int x, int y, SnakeDirection direction)
			: length(length), velocity(velocity), head(new SnakeNode(x, y, direction))
		{
			SnakeNode* current = head;
			for (int i = 1; i < length; i++)
			{
				switch (direction)
				{
				case SD_DOWN:
					y -= 1;
					break;
				case SD_UP:
					y += 1;
					break;
				case SD_LEFT:
					x += 1;
					break;
				case SD_RIGHT:
					x -= 1;
					break;
				}
				SnakeNode* new_node = new SnakeNode(x, y, direction);
				new_node->next = current->next;
				current->next = new_node;
				current = current->next;
			}
		}
	};

	/* 蛇资产路径 */
	const int SNAKE_IMG_NUM = 9;
	const std::wstring snake_img_paths[] = {
		L"assets/GluttonousSnake/imgs/snake/snake_body.png",
		L"assets/GluttonousSnake/imgs/snake/snake_head_down.png",
		L"assets/GluttonousSnake/imgs/snake/snake_head_up.png",
		L"assets/GluttonousSnake/imgs/snake/snake_head_left.png",
		L"assets/GluttonousSnake/imgs/snake/snake_head_right.png",
		L"assets/GluttonousSnake/imgs/snake/snake_body_tail_down.png",
		L"assets/GluttonousSnake/imgs/snake/snake_body_tail_up.png",
		L"assets/GluttonousSnake/imgs/snake/snake_body_tail_left.png",
		L"assets/GluttonousSnake/imgs/snake/snake_body_tail_right.png",
	};

	/* 蛇图片索引 */
	enum SnakeImg
	{
		SI_SNAKE_BODY = 0,
		SI_SNAKE_HEAD_DOWN = 1,
		SI_SNAKE_HEAD_UP = 2,
		SI_SNAKE_HEAD_LEFT = 3,
		SI_SNAKE_HEAD_RIGHT = 4,
		SI_SNAKE_BODY_TAIL_DOWN = 5,
		SI_SNAKE_BODY_TAIL_UP = 6,
		SI_SNAKE_BODY_TAIL_LEFT = 7,
		SI_SNAKE_BODY_TAIL_RIGHT = 8,
	};

	/* 蛇元素图片 */
	extern IMAGE snake_imgs[SNAKE_IMG_NUM];

	/* 声明蛇 */
	extern Snake snake;
}