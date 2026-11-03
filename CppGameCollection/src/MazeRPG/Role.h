#pragma once

#include <string>

#include <graphics.h>

#include "../Utils.h"

namespace maze_rpg
{
	/* 敌人数量 */
	const int ENEMY_NUM = 5;

	/* 人物名字长度 */
	const int ROLE_NAME_LENGTH = 20;

	/* 人物类别 */
	enum RoleType
	{
		RT_HERO = 0,
		RT_ENEMY_SWORD = 1,
		RT_ENEMY_GUN = 2,
	};

	/* 人物朝向 */
	enum RoleDirection
	{
		RD_DOWN = 0,
		RD_LEFT = 1,
		RD_RIGHT = 2,
		RD_UP = 3,
	};

	struct Position
	{
		int x;
		int y;
		Position() {}
		Position(int x, int y) : x(x), y(y) {}

		auto operator<=>(const Position&) const = default;
	};

	/* 人物 */
	struct Role
	{
		bool is_alive = true;
		RoleType type;
		char name[ROLE_NAME_LENGTH];

		int hp;
		int atk;
		int def;

		Position pos;
		RoleDirection direction;

		Role() {}

		Role(RoleType type, int x, int y) : type(type), pos(x, y)
		{
			this->is_alive = true;

			if (type == RT_HERO)
			{
				strcpy_s(name, "Hero");
				hp = 100;
				atk = 20;
				def = 10;
				this->direction = RD_LEFT;
			}
			else if (type == RT_ENEMY_SWORD)
			{
				strcpy_s(name, "Enemy Sword");
				hp = 50;
				atk = 15;
				def = 5;
				this->direction = RD_RIGHT;
			}
			else if (type == RT_ENEMY_GUN)
			{
				strcpy_s(name, "Enemy Gun");
				hp = 30;
				atk = 25;
				def = 3;
				this->direction = RD_RIGHT;
			}
		}
	};

	/* 人物资产路径 */
	const int ROLE_IMG_NUM = 8;
	const std::wstring role_img_paths[] = {
		L"assets/MazeRPG/img/roles/enemy_gun.png",
		L"assets/MazeRPG/img/roles/enemy_gun_got_attacked.png",
		L"assets/MazeRPG/img/roles/enemy_sword.png",
		L"assets/MazeRPG/img/roles/enemy_sword_got_attacked.png",
		L"assets/MazeRPG/img/roles/hero.png",
		L"assets/MazeRPG/img/roles/hero_got_attacked.png",
		L"assets/MazeRPG/img/roles/hero_left.png",
		L"assets/MazeRPG/img/roles/hero_right.png",
	};

	enum RoleImg
	{
		RI_ENEMY_GUN = 0,
		RI_ENEMY_GUN_GOT_ATTACKED = 1,
		RI_ENEMY_SWORD = 2,
		RI_ENEMY_SWORD_GOT_ATTACKED = 3,
		RI_HERO = 4,
		RI_HERO_GOT_ATTACKED = 5,
		RI_HERO_LEFT = 6,
		RI_HERO_RIGHT = 7,
	};

	/* 人物战斗图片大小 */
	const int ROLE_BATTLE_SIZE = 96;

	/* 人物元素图片 */
	extern IMAGE role_imgs[ROLE_IMG_NUM];

	/* 初始化英雄 */
	extern Role hero;

	/* 初始化敌人 */
	extern Role enemies[ENEMY_NUM];
}