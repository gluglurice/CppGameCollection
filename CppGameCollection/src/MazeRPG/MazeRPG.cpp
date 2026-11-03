#include "MazeRPG.h"

namespace maze_rpg
{
	int enemy_num = ENEMY_NUM;
	std::map<Position, int> enemy_map;
	bool game_finish = false;

	void LoadMapAssets()
	{
		/* 加载地图图片 */
		for (int i = 0; i < MAP_IMG_NUM; i++)
		{
			std::wstring index = std::to_wstring(i);
			if (index.length() < 4)
			{
				index.insert(0, 4 - index.length(), L'0');
			}
			map_img_paths[i] = MAP_IMGS_ROOT_PATH + L"/tile_" + index + L".png";
			loadimage(&map_imgs[i], map_img_paths[i].c_str());
		}

		/* 加载地图状态数据 */
		int enemy_id = 0;
		for (int layer = 0; layer < MAP_LAYER_NUM; layer++)
		{
			std::ifstream map_file(MAP_PATHS[layer], std::ios::in);
			if (!map_file.is_open())
			{
				std::cerr << "打开" << MAP_PATHS[layer] << "失败" << std::endl;
				return;
			}
			for (int row = 0; row < MAP_HEIGHT; row++)
			{
				for (int col = 0; col < MAP_WIDTH; col++)
				{
					map_file >> map_status_original[layer][row][col];
					if (layer == MAP_LAYER_NUM - 1)
					{
						if (map_status_original[layer][row][col] == ME_ROLES_ENEMY_SWORD
							|| map_status_original[layer][row][col] == ME_ROLES_ENEMY_GUN)
						{
							enemies[enemy_id] = Role(
								map_status_original[layer][row][col] == ME_ROLES_ENEMY_SWORD ? RT_ENEMY_SWORD : RT_ENEMY_GUN,
								col,
								row
							);
							enemy_map[enemies[enemy_id].pos] = enemy_id;
							enemy_id++;
						}
						else if (map_status_original[layer][row][col] == ME_ROLES_HERO)
						{
							hero = Role(RT_HERO, col, row);
						}
					}
				}
			}
			map_file.close();
		}

		/* 加载回合制战斗地图状态数据 */
		std::ifstream battle_file(MAP_BATTLE_PATH, std::ios::in);
		if (battle_file.is_open())
		{
			for (int row = 0; row < MAP_HEIGHT; row++)
			{
				for (int col = 0; col < MAP_WIDTH; col++)
				{
					battle_file >> map_battle_status_original[row][col];
				}
			}
			battle_file.close();
		}
	}

	void LoadRoleAssets()
	{
		for (int i = 0; i < ROLE_IMG_NUM; i++)
		{
			loadimage(&role_imgs[i], role_img_paths[i].c_str());
		}
	}

	void LoadAssets()
	{
		LoadMapAssets();
		LoadRoleAssets();
	}

	void InitGameStatus()
	{
		/* 初始化地图状态 **/
		memcpy(map_status, map_status_original, sizeof map_status_original);
		memcpy(map_battle_status, map_battle_status_original, sizeof map_battle_status_original);
	}

	void DrawTips()
	{
		outtextxy(GRAPH_WIDTH - TIP_BAR_WIDTH + 15, GRAPH_HEIGHT * 0.6, L"移动：wasd");
		outtextxy(GRAPH_WIDTH - TIP_BAR_WIDTH + 15, GRAPH_HEIGHT * 0.65, L"重置关卡：r");
		outtextxy(GRAPH_WIDTH - TIP_BAR_WIDTH + 15, GRAPH_HEIGHT * 0.7, L"攻击：空格 (回合制内)");
		outtextxy(GRAPH_WIDTH - TIP_BAR_WIDTH + 15, GRAPH_HEIGHT * 0.8, L"消灭完所有敌人即可过关");
	}

	void DrawMap()
	{
		for (int layer = 0; layer < MAP_LAYER_NUM - 1; layer++)
		{
			for (int row = 0; row < MAP_HEIGHT; row++)
			{
				for (int col = 0; col < MAP_WIDTH; col++)
				{
					putimage_alpha_zoom(
						col * TILE_SIZE * MAP_SCALE,
						row * TILE_SIZE * MAP_SCALE,
						TILE_SIZE * MAP_SCALE,
						TILE_SIZE * MAP_SCALE,
						&map_imgs[map_status[layer][row][col] - 1]
					);
				}
			}
		}
	}

	void DrawRole(Role role, RoleImg img_type)
	{
		putimage_alpha_zoom(
			role.pos.x * TILE_SIZE * MAP_SCALE,
			role.pos.y * TILE_SIZE * MAP_SCALE,
			TILE_SIZE * MAP_SCALE,
			TILE_SIZE * MAP_SCALE,
			&role_imgs[img_type]
		);
	}

	void DrawRole()
	{
		if (hero.direction == RD_LEFT)
		{
			DrawRole(hero, RI_HERO_LEFT);
		}
		else if (hero.direction == RD_RIGHT)
		{
			DrawRole(hero, RI_HERO_RIGHT);
		}

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemies[i].is_alive && enemies[i].type == RT_ENEMY_SWORD)
			{
				DrawRole(enemies[i], RI_ENEMY_SWORD);
			}
			else if (enemies[i].is_alive && enemies[i].type == RT_ENEMY_GUN)
			{
				DrawRole(enemies[i], RI_ENEMY_GUN);
			}
		}
	}

	void DrawRoleStatus()
	{
		std::wstring hp = std::to_wstring(hero.hp);
		if (hp.length() < 3)
		{
			hp.insert(0, 3 - hp.length(), L'0');
		}
		outtextxy(GRAPH_WIDTH - TIP_BAR_WIDTH + 50, GRAPH_HEIGHT * 0.3, (L"HP: " + hp).c_str());
	}

	void DrawBattleMap()
	{
		for (int row = 0; row < MAP_HEIGHT; row++)
		{
			for (int col = 0; col < MAP_WIDTH; col++)
			{
				putimage_alpha_zoom(
					col * TILE_SIZE * MAP_SCALE,
					row * TILE_SIZE * MAP_SCALE,
					TILE_SIZE * MAP_SCALE,
					TILE_SIZE * MAP_SCALE,
					&map_imgs[map_battle_status[row][col] - 1]
				);
			}
		}
	}

	void DrawBattle(RoleType enemy_type, RoleType attacker_type, bool is_attacking)
	{
		RoleImg enemy_img = (enemy_type == RT_ENEMY_SWORD) ? RI_ENEMY_SWORD : RI_ENEMY_GUN;

		putimage_alpha_zoom(
			GRAPH_WIDTH * 0.1,
			GRAPH_HEIGHT * 0.3,
			ROLE_BATTLE_SIZE* MAP_SCALE,
			ROLE_BATTLE_SIZE* MAP_SCALE,
			&role_imgs[enemy_img]
		);
		putimage_alpha_zoom(
			GRAPH_WIDTH * 0.5,
			GRAPH_HEIGHT * 0.3,
			ROLE_BATTLE_SIZE* MAP_SCALE,
			ROLE_BATTLE_SIZE* MAP_SCALE,
			&role_imgs[RI_HERO]
		);

		if (is_attacking)
		{
			if (attacker_type == RT_HERO)
			{
				DrawBattleMap();
				DrawRoleStatus();
				DrawTips();

				putimage_alpha_zoom(
					GRAPH_WIDTH * 0.1 - 20,
					GRAPH_HEIGHT * 0.3,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					&role_imgs[(enemy_type == RT_ENEMY_SWORD) ? RI_ENEMY_SWORD_GOT_ATTACKED : RI_ENEMY_GUN_GOT_ATTACKED]
				);
				putimage_alpha_zoom(
					GRAPH_WIDTH * 0.5,
					GRAPH_HEIGHT * 0.3,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					&role_imgs[RI_HERO]
				);

				Sleep(SLEEP_TIME);

				DrawBattleMap();
				DrawRoleStatus();
				DrawTips();

				putimage_alpha_zoom(
					GRAPH_WIDTH * 0.1,
					GRAPH_HEIGHT * 0.3,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					&role_imgs[enemy_type == RT_ENEMY_SWORD ? RI_ENEMY_SWORD : RI_ENEMY_GUN]
				);
				putimage_alpha_zoom(
					GRAPH_WIDTH * 0.5,
					GRAPH_HEIGHT * 0.3,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					&role_imgs[RI_HERO]
				);
			}
			else
			{
				DrawBattleMap();
				DrawRoleStatus();
				DrawTips();

				putimage_alpha_zoom(
					GRAPH_WIDTH * 0.1,
					GRAPH_HEIGHT * 0.3,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					&role_imgs[(enemy_type == RT_ENEMY_SWORD) ? RI_ENEMY_SWORD : RI_ENEMY_GUN]
				);
				putimage_alpha_zoom(
					GRAPH_WIDTH * 0.5 + 20,
					GRAPH_HEIGHT * 0.3,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					&role_imgs[RI_HERO_GOT_ATTACKED]
				);

				Sleep(SLEEP_TIME);

				DrawBattleMap();
				DrawRoleStatus();
				DrawTips();

				putimage_alpha_zoom(
					GRAPH_WIDTH * 0.1,
					GRAPH_HEIGHT * 0.3,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					&role_imgs[enemy_type == RT_ENEMY_SWORD ? RI_ENEMY_SWORD : RI_ENEMY_GUN]
				);
				putimage_alpha_zoom(
					GRAPH_WIDTH * 0.5,
					GRAPH_HEIGHT * 0.3,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					ROLE_BATTLE_SIZE * MAP_SCALE,
					&role_imgs[RI_HERO]
				);
			}
		}
	}

	bool CheckMapWalkable(int terrain, int rail, int environment)
	{
		return (rail == ME_RAIL_BRIDGE
			|| rail == ME_RAIL_HORIZONTAL_MID
			|| rail == ME_RAIL_HORIZONTAL_RIGHT
			|| rail == ME_RAIL_VERTICAL_MID
			|| rail == ME_RAIL_TURN_UPPER_LEFT
			|| rail == ME_RAIL_TURN_UPPER_MID
			|| rail == ME_RAIL_TURN_UPPER_RIGHT
			|| rail == ME_RAIL_TURN_LOWER_LEFT
			|| rail == ME_RAIL_TURN_LOWER_RIGHT)
			||
			((terrain == ME_TERRAIN_LAND_FLAT
				|| terrain == ME_TERRAIN_LAND_GRASS
				|| terrain == ME_TERRAIN_LAND_FLOWER)
				&& environment == ME_EMPTY);
	}

	void Attack(Role& attacker, Role& defender)
	{
		int damage = attacker.atk - defender.def;
		if (damage < 0)
		{
			damage = 0;
		}
		defender.hp -= damage;
		if (defender.hp <= 0)
		{
			defender.hp = 0;
			defender.is_alive = false;
			map_status[ML_ROLES][defender.pos.y][defender.pos.x] = ME_EMPTY;
			if (defender.type == RT_ENEMY_SWORD || defender.type == RT_ENEMY_GUN)
			{
				enemy_num--;
			}
		}
	}

	void EnterBattle(Role& attacker, Role& defender, RoleType enemy_type)
	{
		cleardevice();
		FlushBatchDraw();

		while (attacker.hp > 0 && defender.hp > 0)
		{
			DrawBattleMap();
			DrawBattle(enemy_type, attacker.type, false);
			DrawRoleStatus();
			DrawTips();

			while (char key = _getch())
			{
				if (key == ' ')
				{
					Attack(attacker, defender);
					DrawBattle(enemy_type, attacker.type, true);

					if (defender.hp <= 0)
					{
						break;
					}

					Sleep(SLEEP_TIME);

					Attack(defender, attacker);
					DrawBattle(enemy_type, defender.type, true);

					break;
				}
			}
		}
	}

	void MoveRole(Role& role, RoleDirection rd, int move_x, int move_y)
	{
		if (rd == RD_LEFT || rd == RD_RIGHT)
		{
			role.direction = rd;
		}
		int role_x_new = role.pos.x + move_x;
		int role_y_new = role.pos.y + move_y;

		if (role_x_new < 0 || role_x_new >= MAP_WIDTH || role_y_new < 0 || role_y_new >= MAP_HEIGHT)
		{
			return;
		}

		if (map_status[ML_ROLES][role_y_new][role_x_new] == ME_ROLES_ENEMY_SWORD
			|| map_status[ML_ROLES][role_y_new][role_x_new] == ME_ROLES_ENEMY_GUN)
		{
			Role* enemy = &enemies[enemy_map[Position(role_x_new, role_y_new)]];
			EnterBattle(role, *enemy, enemy->type);
			cleardevice();
			FlushBatchDraw();
			DrawRoleStatus();
		}

		if (CheckMapWalkable(
			map_status[ML_TERRAIN][role_y_new][role_x_new],
			map_status[ML_RAIL][role_y_new][role_x_new],
			map_status[ML_ENVIRONMENT][role_y_new][role_x_new]))
		{
			role.pos.x = role_x_new;
			role.pos.y = role_y_new;
		}
	}

	bool CheckGameWin()
	{
		if (enemy_num <= 0)
		{
			outtextxy(
				GRAPH_WIDTH *0.3,
				GRAPH_HEIGHT * 0.45,
				L"过关了！按任意键退出游戏..."
			);
			return true;
		}
		return false;
	}

	void GameLoop()
	{
		DrawMap();
		DrawRole();
		DrawRoleStatus();
		DrawTips();

		while (true)
		{
			char key = _getch();
			switch (key)
			{
			case 'w':
			case 'W':
				MoveRole(hero, RD_UP, 0, -1);
				break;
			case 's':
			case 'S':
				MoveRole(hero, RD_DOWN, 0, 1);
				break;
			case 'a':
			case 'A':
				MoveRole(hero, RD_LEFT, -1, 0);
				break;
			case 'd':
			case 'D':
				MoveRole(hero, RD_RIGHT, 1, 0);
				break;
			case 'r':
			case 'R':
				cleardevice();
				FlushBatchDraw();
				LoadMapAssets();
				InitGameStatus();
				DrawMap();
				DrawRole();
				DrawRoleStatus();
				DrawTips();
				break;
			}

			DrawMap();
			DrawRole();
			DrawRoleStatus();
			DrawTips();

			/* 当前关卡获胜  */
			game_finish = CheckGameWin();

			/* 全部关卡获胜  */
			if (game_finish)
			{
				break;
			}
		}
	}

	void MazeRPG()
	{
		initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);

		LoadAssets();
		InitGameStatus();

		GameLoop();

		_getch();
		closegraph();
	}
}
