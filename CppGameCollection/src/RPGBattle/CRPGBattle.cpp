#include "CRPGBattle.h"

CRPGBattle::CRPGBattle()
{
	SetGameFinish(false);
	SetAssetsManager(CRPGBattleAssetsManager());
	SetMap(CRPGBattleMap());
	SetHero(CRPGBattleRole(CRPGBattleRole::RT_HERO, "Hero"));
	SetEnemy(CRPGBattleRole(CRPGBattleRole::RT_ENEMY_SWORD, "Enemy Sword"));
}

CRPGBattle::~CRPGBattle() {}

void CRPGBattle::InitGameStatus()
{
	m_map.InitMapStatus();
}

void CRPGBattle::DrawUI()
{
	/* Set font */
	setbkmode(TRANSPARENT);
	settextcolor(RGB(0x6D, 0x4B, 0x27));
	settextstyle(20, 0, _T("微软雅黑"), 0, 0, FW_BOLD, FALSE, FALSE, FALSE);

	/* Draw UI background */
	putimage_alpha_zoom(
		m_map.GetMapWidth() * m_map.GetTileSize() * CRPGBattleAssetsManager::SCALE,
		0,
		1,
		&m_assets_manager.GetUIImgs()[CRPGBattleAssetsManager::UII_BACKGROUND]
	);

	/* Draw UI HP */
	const int UI_HP_WIDTH_LEFT = 134;
	const float UI_HP_HEIGHT_FACTOR = 0.4f;
	outtextxy(
		m_map.GetGraphWidth() - UI_HP_WIDTH_LEFT,
		m_map.GetGraphHeight() * UI_HP_HEIGHT_FACTOR,
		(L"HP: " + std::to_wstring(m_hero.GetHP())).c_str()
	);


	/* Draw UI keys */
	const int UI_KEY_WIDTH_MID = 130;
	const int UI_KEY_SIZE = 48;
	const int UI_KEY_SCALE = 1;
	const float UI_KEY_HEIGHT_FACTOR = 0.6f;

	putimage_alpha_zoom(
		m_map.GetGraphWidth() - UI_KEY_WIDTH_MID - UI_KEY_SIZE - 8,
		m_map.GetGraphHeight() * UI_KEY_HEIGHT_FACTOR,
		CRPGBattleAssetsManager::SCALE * UI_KEY_SCALE,
		&m_assets_manager.GetUIImgs()[CRPGBattleAssetsManager::UII_KEYBOARD_SPACE]
	);
	outtextxy(
		m_map.GetGraphWidth() - UI_KEY_WIDTH_MID + 8,
		m_map.GetGraphHeight() * UI_KEY_HEIGHT_FACTOR + 64,
		_T("Attack")
	);
}

void CRPGBattle::DrawRoleStatus()
{
	std::wstring hp = std::to_wstring(m_hero.GetHP());
	if (hp.length() < 3)
	{
		hp.insert(0, 3 - hp.length(), L'0');
	}
	outtextxy(m_map.GetGraphWidth() - CRPGBattleAssetsManager::TIP_BAR_WIDTH + 50, m_map.GetGraphHeight() * 0.3, (L"HP: " + hp).c_str());
}

void CRPGBattle::DrawBattleMap()
{
	for (int row = 0; row < m_map.GetMapHeight(); row++)
	{
		for (int col = 0; col < m_map.GetMapWidth(); col++)
		{
			putimage_alpha_zoom(
				col * m_map.GetTileSize() * CRPGBattleAssetsManager::SCALE,
				row * m_map.GetTileSize() * CRPGBattleAssetsManager::SCALE,
				m_map.GetTileSize() * CRPGBattleAssetsManager::SCALE,
				m_map.GetTileSize() * CRPGBattleAssetsManager::SCALE,
				&m_assets_manager.GetMapImgs()[m_map.GetMapStatus()[CRPGBattleMap::ML_TERRAIN][row][col] - 1]
			);
		}
	}
}

void CRPGBattle::DrawBattle(CRPGBattleRole::RoleType enemy_type, CRPGBattleRole::RoleType attacker_type, bool is_attacking)
{
	CRPGBattleAssetsManager::RoleImg enemy_img = 
		(enemy_type == CRPGBattleRole::RT_ENEMY_SWORD) ? 
		CRPGBattleAssetsManager::RI_ENEMY_SWORD : 
		CRPGBattleAssetsManager::RI_ENEMY_GUN;

	putimage_alpha_zoom(
		m_map.GetGraphWidth() * 0.1,
		m_map.GetGraphHeight() * 0.3,
		CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
		CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
		&m_assets_manager.GetRoleImgs()[enemy_img]
	);
	putimage_alpha_zoom(
		m_map.GetGraphWidth() * 0.5,
		m_map.GetGraphHeight() * 0.3,
		CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
		CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
		&m_assets_manager.GetRoleImgs()[CRPGBattleAssetsManager::RI_HERO]
	);

	if (is_attacking)
	{
		if (attacker_type == CRPGBattleRole::RT_HERO)
		{
			DrawBattleMap();
			DrawRoleStatus();
			DrawUI();

			putimage_alpha_zoom(
				m_map.GetGraphWidth() * 0.1 - 20,
				m_map.GetGraphHeight() * 0.3,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				&m_assets_manager.GetRoleImgs()[(enemy_type == CRPGBattleRole::RT_ENEMY_SWORD) ? CRPGBattleAssetsManager::RI_ENEMY_SWORD_GOT_ATTACKED : CRPGBattleAssetsManager::RI_ENEMY_GUN_GOT_ATTACKED]
			);
			putimage_alpha_zoom(
				m_map.GetGraphWidth() * 0.5,
				m_map.GetGraphHeight() * 0.3,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				&m_assets_manager.GetRoleImgs()[CRPGBattleAssetsManager::RI_HERO]
			);

			Sleep(SLEEP_TIME);

			DrawBattleMap();
			DrawRoleStatus();
			DrawUI();

			putimage_alpha_zoom(
				m_map.GetGraphWidth() * 0.1,
				m_map.GetGraphHeight() * 0.3,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				&m_assets_manager.GetRoleImgs()[enemy_type == CRPGBattleRole::RT_ENEMY_SWORD ? CRPGBattleAssetsManager::RI_ENEMY_SWORD : CRPGBattleAssetsManager::RI_ENEMY_GUN]
			);
			putimage_alpha_zoom(
				m_map.GetGraphWidth() * 0.5,
				m_map.GetGraphHeight() * 0.3,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				&m_assets_manager.GetRoleImgs()[CRPGBattleAssetsManager::RI_HERO]
			);
		}
		else
		{
			DrawBattleMap();
			DrawRoleStatus();
			DrawUI();

			putimage_alpha_zoom(
				m_map.GetGraphWidth() * 0.1,
				m_map.GetGraphHeight() * 0.3,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				&m_assets_manager.GetRoleImgs()[(enemy_type == CRPGBattleRole::RT_ENEMY_SWORD) ? CRPGBattleAssetsManager::RI_ENEMY_SWORD : CRPGBattleAssetsManager::RI_ENEMY_GUN]
			);
			putimage_alpha_zoom(
				m_map.GetGraphWidth() * 0.5 + 20,
				m_map.GetGraphHeight() * 0.3,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				&m_assets_manager.GetRoleImgs()[CRPGBattleAssetsManager::RI_HERO_GOT_ATTACKED]
			);

			Sleep(SLEEP_TIME);

			DrawBattleMap();
			DrawRoleStatus();
			DrawUI();

			putimage_alpha_zoom(
				m_map.GetGraphWidth() * 0.1,
				m_map.GetGraphHeight() * 0.3,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				&m_assets_manager.GetRoleImgs()[enemy_type == CRPGBattleRole::RT_ENEMY_SWORD ? CRPGBattleAssetsManager::RI_ENEMY_SWORD : CRPGBattleAssetsManager::RI_ENEMY_GUN]
			);
			putimage_alpha_zoom(
				m_map.GetGraphWidth() * 0.5,
				m_map.GetGraphHeight() * 0.3,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				CRPGBattleAssetsManager::ROLE_BATTLE_SIZE * CRPGBattleAssetsManager::SCALE,
				&m_assets_manager.GetRoleImgs()[CRPGBattleAssetsManager::RI_HERO]
			);
		}
	}
}

void CRPGBattle::DrawBattleFinishUI(CRPGBattleRole::RoleType winner_type)
{
	std::wstring winner_text;
	if (winner_type == CRPGBattleRole::RT_HERO)
	{
		winner_text = L"You win!";
	}
	else
	{
		winner_text = L"You lose!";
	}

	/* Draw UI Tips */
	const int UI_TIPS_WIDTH_LEFT = 134;
	const float UI_TIPS_HEIGHT_FACTOR = 0.5f;
	outtextxy(
		m_map.GetGraphWidth() - UI_TIPS_WIDTH_LEFT,
		m_map.GetGraphHeight() * UI_TIPS_HEIGHT_FACTOR,
		winner_text.c_str()
	);
}

void CRPGBattle::DrawAll()
{
	DrawBattleMap();
	DrawRoleStatus();
	DrawUI();
}

void CRPGBattle::EnterBattle(CRPGBattleRole& attacker, CRPGBattleRole& defender, CRPGBattleRole::RoleType enemy_type)
{
	cleardevice();
	FlushBatchDraw();

	while (attacker.GetHP() > 0 && defender.GetHP() > 0)
	{
		DrawAll();
		DrawBattle(enemy_type, attacker.GetType(), false);

		while (char key = _getch())
		{
			if (key == ' ')
			{
				attacker.Attack(defender);
				DrawBattle(enemy_type, attacker.GetType(), true);

				if (defender.GetHP() <= 0)
				{
					m_game_finish = true;
					DrawBattleFinishUI(CRPGBattleRole::RT_HERO);
					break;
				}

				Sleep(SLEEP_TIME);

				defender.Attack(attacker);
				DrawBattle(enemy_type, defender.GetType(), true);
				if (attacker.GetHP() <= 0)
				{
					m_game_finish = true;
					DrawBattleFinishUI(CRPGBattleRole::RT_ENEMY_SWORD);
					break;
				}
			}
		}
	}
}

void CRPGBattle::GameLoop()
{
	while (!m_game_finish)
	{
		DrawRoleStatus();
		DrawUI();
		EnterBattle(m_hero, m_enemy, m_enemy.GetType());
	}
}

void CRPGBattle::RunGame()
{
	m_assets_manager.LoadAssets();

	m_map.LoadMapOriginalStatus(CRPGBattleAssetsManager::MAP_BATTLE_PATH);
	initgraph(m_map.GetGraphWidth(), m_map.GetGraphHeight());

	InitGameStatus();

	GameLoop();

	_getch();
	closegraph();
}

bool CRPGBattle::GetGameFinish()
{
	return m_game_finish;
}

void CRPGBattle::SetGameFinish(bool game_finish)
{
	m_game_finish = game_finish;
}

CRPGBattleAssetsManager CRPGBattle::GetAssetsManager()
{
	return m_assets_manager;
}

void CRPGBattle::SetAssetsManager(CRPGBattleAssetsManager assets_manager)
{
	m_assets_manager = assets_manager;
}

CRPGBattleMap CRPGBattle::GetMap()
{
	return m_map;
}

void CRPGBattle::SetMap(CRPGBattleMap map)
{
	m_map = map;
}

CRPGBattleRole CRPGBattle::GetHero()
{
	return m_hero;
}

void CRPGBattle::SetHero(CRPGBattleRole hero)
{
	m_hero = hero;
}

CRPGBattleRole CRPGBattle::GetEnemy()
{
	return m_enemy;
}

void CRPGBattle::SetEnemy(CRPGBattleRole enemy)
{
	m_enemy = enemy;
}
