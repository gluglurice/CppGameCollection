#include "CSokobanV2.h"

CSokobanV2::CSokobanV2() :
	m_game_finish(false),
	m_assets_manager(CSokobanV2AssetsManager()),
	m_level_manager(CSokobanV2LevelManager()),
	m_map(m_level_manager.GetMapPaths()[m_level_manager.GetCurrentLevel()]),
	m_role(CSokobanV2Role(m_map.GetRoleStartPosition(), CSokobanV2Role::RD_DOWN)) {}

CSokobanV2::~CSokobanV2() {}

void CSokobanV2::InitGameStatus()
{
	m_map.InitMapStatus();
	m_role.SetPosition(m_map.GetRoleStartPosition());
	m_role.SetDirection(CSokobanV2Role::RD_DOWN);
}

void CSokobanV2::DrawUI()
{
	/* Set font */
	setbkmode(TRANSPARENT);
	settextcolor(RGB(0x6D, 0x4B, 0x27));
	settextstyle(20, 0, _T("微软雅黑"), 0, 0, FW_BOLD, FALSE, FALSE, FALSE);

	/* Draw UI background */
	putimage_alpha_zoom(
		m_map.GetMapWidth() * m_map.GetTileSize() * CSokobanV2AssetsManager::SCALE,
		0,
		1,
		&m_assets_manager.GetUIImgs()[CSokobanV2AssetsManager::UII_BACKGROUND]
	);

	/* Draw UI keys */
	const int UI_KEY_WIDTH_MID = 130;
	const int UI_KEY_SIZE = 48;
	const int UI_KEY_SCALE = 1;
	const float UI_KEY_HEIGHT_FACTOR = 0.45f;

	putimage_alpha_zoom(
		m_map.GetGraphWidth() - UI_KEY_WIDTH_MID,
		m_map.GetGraphHeight() * UI_KEY_HEIGHT_FACTOR,
		CSokobanV2AssetsManager::SCALE * UI_KEY_SCALE,
		&m_assets_manager.GetUIImgs()[CSokobanV2AssetsManager::UII_KEYBOARD_W]
	);
	putimage_alpha_zoom(
		m_map.GetGraphWidth() - UI_KEY_WIDTH_MID,
		m_map.GetGraphHeight() * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE,
		CSokobanV2AssetsManager::SCALE * UI_KEY_SCALE,
		&m_assets_manager.GetUIImgs()[CSokobanV2AssetsManager::UII_KEYBOARD_S]
	);
	putimage_alpha_zoom(
		m_map.GetGraphWidth() - UI_KEY_WIDTH_MID - UI_KEY_SIZE,
		m_map.GetGraphHeight() * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE,
		CSokobanV2AssetsManager::SCALE * UI_KEY_SCALE,
		&m_assets_manager.GetUIImgs()[CSokobanV2AssetsManager::UII_KEYBOARD_A]
	);
	putimage_alpha_zoom(
		m_map.GetGraphWidth() - UI_KEY_WIDTH_MID + UI_KEY_SIZE,
		m_map.GetGraphHeight() * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE,
		CSokobanV2AssetsManager::SCALE * UI_KEY_SCALE,
		&m_assets_manager.GetUIImgs()[CSokobanV2AssetsManager::UII_KEYBOARD_D]
	);
	outtextxy(
		m_map.GetGraphWidth() - UI_KEY_WIDTH_MID + 12,
		m_map.GetGraphHeight() * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE * 2 + 12,
		_T("Move")
	);

	putimage_alpha_zoom(
		m_map.GetGraphWidth() - UI_KEY_WIDTH_MID - UI_KEY_SIZE - 8,
		m_map.GetGraphHeight() * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE * 3,
		CSokobanV2AssetsManager::SCALE * UI_KEY_SCALE,
		&m_assets_manager.GetUIImgs()[CSokobanV2AssetsManager::UII_KEYBOARD_SPACE]
	);
	outtextxy(
		m_map.GetGraphWidth() - UI_KEY_WIDTH_MID - 16,
		m_map.GetGraphHeight() * UI_KEY_HEIGHT_FACTOR + UI_KEY_SIZE * 4 + 12,
		_T("Reverse level")
	);
}

void CSokobanV2::DrawMap()
{
	for (int row = 0; row < m_map.GetMapHeight(); row++)
	{
		for (int col = 0; col < m_map.GetMapWidth(); col++)
		{
			if (m_map.GetMapStatus()[row][col] != CSokobanV2Map::ME_EMPTY)
			{
				putimage_alpha_zoom(
					col * m_map.GetTileSize() * CSokobanV2AssetsManager::SCALE,
					row * m_map.GetTileSize() * CSokobanV2AssetsManager::SCALE,
					m_map.GetTileSize() * CSokobanV2AssetsManager::SCALE,
					m_map.GetTileSize() * CSokobanV2AssetsManager::SCALE,
					&m_assets_manager.GetMapImgs()[m_map.GetMapStatus()[row][col] - 1]
				);
			}
		}
	}
}

void CSokobanV2::DrawRole()
{
	putimage_alpha_zoom(
		m_role.GetPosition().x * m_map.GetTileSize() * CSokobanV2AssetsManager::SCALE,
		m_role.GetPosition().y * m_map.GetTileSize() * CSokobanV2AssetsManager::SCALE,
		m_map.GetTileSize() * CSokobanV2AssetsManager::SCALE,
		m_map.GetTileSize() * CSokobanV2AssetsManager::SCALE,
		&m_assets_manager.GetRoleImgs()[m_role.GetDirection()]
	);
}

void CSokobanV2::DrawLevelFinishUI()
{
	/* Set font */
	settextcolor(RGB(0x36, 0x40, 0x4A));

	const int UI_TIPS_LEFT_START = (m_map.GetGraphWidth() - CSokobanV2AssetsManager::TIP_BAR_WIDTH) / 4;
	const float UI_TIPS_HEIGHT_START = m_map.GetGraphHeight() * 0.3f;
	const int UI_TIPS_SCALE = 1;

	putimage_alpha_zoom(
		UI_TIPS_LEFT_START,
		UI_TIPS_HEIGHT_START,
		CSokobanV2AssetsManager::SCALE * UI_TIPS_SCALE,
		&m_assets_manager.GetUIImgs()[CSokobanV2AssetsManager::UII_TIPS]
	);
	outtextxy(
		UI_TIPS_LEFT_START + 78,
		UI_TIPS_HEIGHT_START + 54,
		_T("Current level finished!")
	);
	outtextxy(
		UI_TIPS_LEFT_START + 86,
		UI_TIPS_HEIGHT_START + 96,
		_T("Press any button")
	);
	outtextxy(
		UI_TIPS_LEFT_START + 106,
		UI_TIPS_HEIGHT_START + 118,
		_T("to continue...")
	);
}

void CSokobanV2::DrawGameFinishUI()
{
	/* Set font */
	settextcolor(RGB(0x36, 0x40, 0x4A));

	const int UI_TIPS_LEFT_START = (m_map.GetGraphWidth() - CSokobanV2AssetsManager::TIP_BAR_WIDTH) / 4;
	const float UI_TIPS_HEIGHT_START = m_map.GetGraphHeight() * 0.3f;
	const int UI_TIPS_SCALE = 1;

	putimage_alpha_zoom(
		UI_TIPS_LEFT_START,
		UI_TIPS_HEIGHT_START,
		CSokobanV2AssetsManager::SCALE * UI_TIPS_SCALE,
		&m_assets_manager.GetUIImgs()[CSokobanV2AssetsManager::UII_TIPS]
	);
	outtextxy(
		UI_TIPS_LEFT_START + 78,
		UI_TIPS_HEIGHT_START + 54,
		_T("Game finished!")
	);
	outtextxy(
		UI_TIPS_LEFT_START + 86,
		UI_TIPS_HEIGHT_START + 96,
		_T("Press any button")
	);
	outtextxy(
		UI_TIPS_LEFT_START + 106,
		UI_TIPS_HEIGHT_START + 118,
		_T("to continue...")
	);
}

void CSokobanV2::DrawAll()
{
	DrawUI();
	DrawMap();
	DrawRole();
	if (m_game_finish)
	{
		DrawGameFinishUI();
		return;
	}
	if (m_level_manager.CheckLevelFinish(m_map.GetBoxNotInTargetNum()))
	{
		DrawLevelFinishUI();
	}
}

void CSokobanV2::GameLoop()
{
	while (!m_game_finish)
	{
		DrawAll();
		char key = _getch();
		switch (key)
		{
		case 'w':
		case 'W':
			m_role.Move(CSokobanV2Role::RD_UP, 0, -1, m_map);
			break;
		case 's':
		case 'S':
			m_role.Move(CSokobanV2Role::RD_DOWN, 0, 1, m_map);
			break;
		case 'a':
		case 'A':
			m_role.Move(CSokobanV2Role::RD_LEFT, -1, 0, m_map);
			break;
		case 'd':
		case 'D':
			m_role.Move(CSokobanV2Role::RD_RIGHT, 1, 0, m_map);
			break;
		case ' ':
			cleardevice();
			FlushBatchDraw();
			InitGameStatus();
			DrawAll();
			break;
		}

		if (m_level_manager.CheckLevelFinish(m_map.GetBoxNotInTargetNum()))
		{
			if (m_level_manager.GetCurrentLevel() >= m_level_manager.GetLevelNum() - 1)
			{
				m_game_finish = true;
			}
			else
			{
				DrawAll();
				_getch();
				cleardevice();
				FlushBatchDraw();
				m_level_manager.SetCurrentLevel(m_level_manager.GetCurrentLevel() + 1);
				m_map = CSokobanV2Map(m_level_manager.GetMapPaths()[m_level_manager.GetCurrentLevel()]);
				m_role.SetPosition(m_map.GetRoleStartPosition());
				m_role.SetDirection(CSokobanV2Role::RD_DOWN);
			}
		}
	}
	DrawAll();
}

void CSokobanV2::RunGame()
{
	m_assets_manager.LoadAssets();

	initgraph(m_map.GetGraphWidth(), m_map.GetGraphHeight());

	InitGameStatus();

	GameLoop();

	_getch();
	closegraph();
}

bool CSokobanV2::GetGameFinish()
{
	return m_game_finish;
}

void CSokobanV2::SetGameFinish(bool game_finish)
{
	m_game_finish = game_finish;
}

CSokobanV2AssetsManager CSokobanV2::GetAssetsManager()
{
	return m_assets_manager;
}

void CSokobanV2::SetAssetsManager(CSokobanV2AssetsManager assets_manager)
{
	m_assets_manager = assets_manager;
}

CSokobanV2LevelManager CSokobanV2::GetLevelManager()
{
	return m_level_manager;
}

void CSokobanV2::SetLevelManager(CSokobanV2LevelManager level_manager)
{
	m_level_manager = level_manager;
}

CSokobanV2Map CSokobanV2::GetMap()
{
	return m_map;
}

void CSokobanV2::SetMap(CSokobanV2Map map)
{
	for (int row = 0; row < map.GetMapHeight(); row++)
	{
		for (int col = 0; col < map.GetMapWidth(); col++)
		{
			m_map.SetMapElem(row, col, map.GetMapElem(row, col));
		}
	}
}

CSokobanV2Role CSokobanV2::GetRole()
{
	return m_role;
}

void CSokobanV2::SetRole(CSokobanV2Role role)
{
	m_role = role;
}
