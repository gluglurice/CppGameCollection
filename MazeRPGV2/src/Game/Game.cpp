#include "Game.h"

#include "Map.h"
#include "MapFC.h"
#include "Character.h"
#include "CharacterFC.h"
#include "Door.h"
#include "DoorFC.h"

const string CGame::GAME_INI_PATH = "config/game_ini.xml";
const float CGame::ONE_SEC = 1000.0f;

int CGame::GRAPH_WIDTH = 0;
int CGame::GRAPH_HEIGHT = 0;
int CGame::MAP_TILE_SIZE = 0;
int CGame::FPS = 0;
float CGame::DELTA_TIME = 0.0f;
float CGame::SCALE = 1.0f;

vector<CVector3D> CGame::UNIT_VECS = {
	CVector3D(0.0f, 1.0f, 0.0f),
	CVector3D(1.0f, 0.0f, 0.0f),
	CVector3D(0.0f, -1.0f, 0.0f),
	CVector3D(-1.0f, 0.0f, 0.0f),
};

map<int, vector<bool>> CGame::m_key_pressed = {
	{ 'W', { false } },
	{ 'A', { false } },
	{ 'S', { false } },
	{ 'D', { false } },
	{ 'J', { false, false } },
	{ 'K', { false, false } },
};

unsigned CGame::m_moving_key_pressed_count = 0;

LRESULT CGame::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (m_key_pressed.find(wParam) != m_key_pressed.end() && !m_key_pressed[wParam][0])
		{
			m_key_pressed[wParam][0] = true;
			if (wParam == 'W' || wParam == 'A' || wParam == 'S' || wParam == 'D')
			{
				m_moving_key_pressed_count++;
			}
		}
		break;
	case WM_KEYUP:
		if (m_key_pressed.find(wParam) != m_key_pressed.end() && m_key_pressed[wParam][0])
		{
			m_key_pressed[wParam][0] = false;
			if (wParam == 'W' || wParam == 'A' || wParam == 'S' || wParam == 'D')
			{
				m_moving_key_pressed_count--;
			}
			if (wParam == 'J' || wParam == 'K')
			{
				m_key_pressed[wParam][1] = false;
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

CGame::CGame()
{
	/* 加载游戏配置 */
	TiXmlDocument xml_doc;

	if (!xml_doc.LoadFile(GAME_INI_PATH.c_str()))
	{
		cerr << "打开XML文件失败：" << GAME_INI_PATH << endl;
		return;
	}

	TiXmlElement* xml_root = xml_doc.RootElement();

	xml_root->QueryIntAttribute("graph_width", &GRAPH_WIDTH);
	xml_root->QueryIntAttribute("graph_height", &GRAPH_HEIGHT);
	xml_root->QueryIntAttribute("fps", &FPS);
	xml_root->QueryFloatAttribute("delta_time", &DELTA_TIME);
	xml_root->QueryFloatAttribute("scale", &SCALE);

	TiXmlElement* xml_maps = xml_root->FirstChildElement("maps");
	int map_tile_size;
	int map_scale;
	xml_maps->QueryIntAttribute("tile_size", &map_tile_size);
	xml_maps->QueryIntAttribute("scale", &map_scale);
	MAP_TILE_SIZE = map_tile_size * map_scale;

	/* 初始化窗口 */
	auto hwnd = CGraphic::GetInstance()->InitWindow(&WndProc, GRAPH_WIDTH, GRAPH_HEIGHT);
	CGraphic::GetInstance()->InitDX(hwnd);
	CGraphic::GetInstance()->m_pDevice->SetRenderState(D3DRS_ZENABLE, false);

	/* 初始化关卡和角色 */
	m_is_game_quit = false;
	m_level = 0;
	m_map = CMapFC::GetInstance()->GetLevelMap(m_level);
	m_character = CCharacterFC::GetInstance()->CreateCharacter(m_map->GetStartPositionLogic(), CCharacter::C_PLAYER, CCharacter::T_LINK);
}

void CGame::CheckMessage()
{
	while (PeekMessage(&m_msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (m_msg.message == WM_QUIT)
		{
			m_is_game_quit = true;
		}
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}
}

void CGame::ListenLevelChangeEvent()
{
	if (m_key_pressed['J'][0] && !m_key_pressed['J'][1] && m_level > 0)
	{
		m_key_pressed['J'][1] = true;
		m_map = CMapFC::GetInstance()->GetLevelMap(--m_level);
		m_character->SetPositionLogic(m_map->GetStartPositionLogic());
		CVector3D position_render = m_character->GetPositionLogic() * MAP_TILE_SIZE + CVector3D(MAP_TILE_SIZE / 2.0f, MAP_TILE_SIZE / 2.0f, 0.0f);
		m_character->SetPositionRender(position_render);
		m_character->UpdateState(m_character->GetState(), CActor::D_UP);
	}
	if (m_key_pressed['K'][0] && !m_key_pressed['K'][1] && m_level < CMapFC::GetInstance()->GetLevelCount() - 1)
	{
		m_key_pressed['K'][1] = true;
		m_map = CMapFC::GetInstance()->GetLevelMap(++m_level);
		m_character->SetPositionLogic(m_map->GetStartPositionLogic());
		CVector3D position_render = m_character->GetPositionLogic() * MAP_TILE_SIZE + CVector3D(MAP_TILE_SIZE / 2.0f, MAP_TILE_SIZE / 2.0f, 0.0f);
		m_character->SetPositionRender(position_render);
		m_character->UpdateState(m_character->GetState(), CActor::D_UP);
	}
}

void CGame::ListenCharacterIdleEvent()
{
	if (m_moving_key_pressed_count == 0)
	{
		m_character->UpdateState(CCharacter::S_IDLE, m_character->GetDirection());
		m_character->Idle();
		m_character->Update();
	}

	if (m_character->GetState() == CCharacter::S_IDLE)
	{
		CActor::Direction direction = m_character->GetDirection();
		if (m_key_pressed['W'][0])
		{
			direction = CActor::D_UP;
		}
		if (m_key_pressed['S'][0])
		{
			direction = CActor::D_DOWN;
		}
		if (m_key_pressed['A'][0])
		{
			direction = CActor::D_LEFT;
		}
		if (m_key_pressed['D'][0])
		{
			direction = CActor::D_RIGHT;
		}
		m_character->UpdateState(CCharacter::S_IDLE, direction);
		if (m_moving_key_pressed_count > 0)
		{
			m_character->DetectCollision(m_map, m_character->GetPositionLogic() + UNIT_VECS[direction]);
		}
	}
}

void CGame::ListenCharacterMoveEvent()
{
	if (m_character->GetState() == CCharacter::S_MOVE)
	{
		unsigned tick = clock();
		CVector3D remaining_offset = m_character->GetTargetPositionRender() - m_character->GetPositionRender();
		while (remaining_offset.Length() >= m_character->GetVelocity())
		{
			if (clock() - tick >= ONE_SEC / FPS)
			{
				remaining_offset = m_character->GetTargetPositionRender() - m_character->GetPositionRender();
				if (remaining_offset.Length() < m_character->GetVelocity())
				{
					m_character->MoveRender(remaining_offset);
					m_character->Update();
				}
				else
				{
					m_character->MoveRender(UNIT_VECS[m_character->GetDirection()] * m_character->GetVelocity());
					m_character->Update();
				}
				Draw();
				tick = clock();
				CheckMessage();
			}
		}
		m_character->MoveLogic(m_character->GetTargetPositionLogic() - m_character->GetPositionLogic());

		CActor::Direction direction = m_character->GetDirection();
		if (m_key_pressed['W'][0])
		{
			direction = CActor::D_UP;
		}
		if (m_key_pressed['S'][0])
		{
			direction = CActor::D_DOWN;
		}
		if (m_key_pressed['A'][0])
		{
			direction = CActor::D_LEFT;
		}
		if (m_key_pressed['D'][0])
		{
			direction = CActor::D_RIGHT;
		}
		m_character->UpdateState(CCharacter::S_IDLE, direction);
		if (m_moving_key_pressed_count > 0)
		{
			m_character->DetectCollision(m_map, m_character->GetPositionLogic() + UNIT_VECS[direction]);
		}
	}
}

void CGame::ListenDoorOpenEvent()
{
	for (auto& pair : m_map->GetObjects())
	{
		CDoor* door = dynamic_cast<CDoor*>(pair.second);
		CDoor* door_right = nullptr;
		CDoor* door_left = nullptr;
		if (!door)
		{
			continue;
		}
		if (door->GetType() == CDoor::T_DOUBLE_LEFT)
		{
			door_right = dynamic_cast<CDoor*>(m_map->GetObjects()[door->GetPositionLogic() + CGame::UNIT_VECS[CActor::D_RIGHT]]);
		}
		if (door->GetType() == CDoor::T_DOUBLE_RIGHT)
		{
			door_left = dynamic_cast<CDoor*>(m_map->GetObjects()[door->GetPositionLogic() + CGame::UNIT_VECS[CActor::D_LEFT]]);
		}
		if (door->GetState() == CActor::S_MOVE)
		{
			unsigned tick = clock();
			int cur_frame = door->GetSprites()[door->GetCurSprite()]->GetCurFrame();
			int frame_count = door->GetSprites()[door->GetCurSprite()]->GetFrameCount();
			while (cur_frame < frame_count - 1)
			{
				if (clock() - tick >= ONE_SEC / FPS)
				{
					door->Update();
					if (door_right)
					{
						door_right->Update();
					}
					if (door_left)
					{
						door_left->Update();
					}
					Draw();
					tick = clock();
					CheckMessage();
					cur_frame = door->GetSprites()[door->GetCurSprite()]->GetCurFrame();
				}
			}
			m_map->OpenDoorLogic(door->GetPositionLogic());
			if (door_right)
			{
				m_map->OpenDoorLogic(door_right->GetPositionLogic());
			}
			if (door_left)
			{
				m_map->OpenDoorLogic(door_left->GetPositionLogic());
			}

			door->SetState(CActor::S_STILL);
			if (door_right)
			{
				door_right->SetState(CActor::S_STILL);
			}
			if (door_left)
			{
				door_left->SetState(CActor::S_STILL);
			}
		}
	}
}

void CGame::Draw()
{
	CGraphic::GetInstance()->BeginDraw();
	m_map->Draw(CMap::L_TERRAIN);
	m_map->Draw(CMap::L_ENVIRONMENT_BACKGROUND);
	m_map->DrawObjects();
	m_character->Draw();
	m_map->Draw(CMap::L_ENVIRONMENT_FOREGROUND);
	CGraphic::GetInstance()->EndDraw();
}

int CGame::WinRun(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	while (!m_is_game_quit)
	{
		CheckMessage();
		Draw();
		ListenLevelChangeEvent();
		ListenCharacterIdleEvent();
		ListenCharacterMoveEvent();
		ListenDoorOpenEvent();
	}

	return 0;
}
