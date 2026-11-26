#include "Game.h"

#include "Map.h"
#include "MapFC.h"
#include "Character.h"
#include "CharacterFC.h"

const string CGame::GAME_INI_PATH = "config/game_ini.xml";
const float CGame::ONE_SEC = 1000.0f;

int CGame::GRAPH_WIDTH;
int CGame::GRAPH_HEIGHT;
int CGame::MAP_TILE_SIZE;
int CGame::FPS;
float CGame::DELTA_TIME;
float CGame::SCALE;

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

	if (!xml_doc.LoadFile(CGame::GAME_INI_PATH.c_str()))
	{
		cerr << "打开XML文件失败：" << CGame::GAME_INI_PATH << endl;
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
	auto hwnd = CGraphic::GetInstance()->InitWindow(&CGame::WndProc, CGame::GRAPH_WIDTH, CGame::GRAPH_HEIGHT);
	CGraphic::GetInstance()->InitDX(hwnd);
	CGraphic::GetInstance()->m_pDevice->SetRenderState(D3DRS_ZENABLE, false);
}

bool CGame::CheckMessageQuit(MSG& msg)
{
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return true;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return false;
}

int CGame::WinRun(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	MSG msg;

	int level = 0;
	CMap* map = CMapFC::GetInstance()->GetLevelMap(level);
	CCharacter* link = CCharacterFC::GetInstance()->CreateCharacter(map->GetStartPositionLogic(), CCharacter::T_PLAYER);
	CVector3D target_position_render = link->GetPositionRender();

	while (true)
	{
		if (CGame::CheckMessageQuit(msg))
		{
			break;
		}

		CGraphic::GetInstance()->BeginDraw();
		map->Draw();
		link->Draw();
		CGraphic::GetInstance()->EndDraw();

		/* 切换关卡地图 */
		if (m_key_pressed['J'][0] && !m_key_pressed['J'][1] && level > 0)
		{
			m_key_pressed['J'][1] = true;
			map = CMapFC::GetInstance()->GetLevelMap(--level);
			link->SetPositionLogic(map->GetStartPositionLogic());
			CVector3D position_render = link->GetPositionLogic() * CGame::MAP_TILE_SIZE + CVector3D(CGame::MAP_TILE_SIZE / 2.0f, CGame::MAP_TILE_SIZE / 2.0f, 0.0f);
			link->SetPositionRender(position_render);
			link->SetDirection(CCharacter::D_UP);
		}
		if (m_key_pressed['K'][0]  && !m_key_pressed['K'][1] && level < CMapFC::GetInstance()->GetLevelCount() - 1)
		{
			m_key_pressed['K'][1] = true;
			map = CMapFC::GetInstance()->GetLevelMap(++level);
			link->SetPositionLogic(map->GetStartPositionLogic());
			CVector3D position_render = link->GetPositionLogic() * CGame::MAP_TILE_SIZE + CVector3D(CGame::MAP_TILE_SIZE / 2.0f, CGame::MAP_TILE_SIZE / 2.0f, 0.0f);
			link->SetPositionRender(position_render);
			link->SetDirection(CCharacter::D_UP);
		}

		if (m_moving_key_pressed_count == 0)
		{
			link->UpdateState(CCharacter::S_IDLE, link->GetDirection());
			link->Idle();
		}

		/* 待机状态 */
		if (link->GetState() == CCharacter::S_IDLE)
		{
			CActor::Direction direction = link->GetDirection();
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
			link->UpdateState(CCharacter::S_IDLE, direction);
			if (m_moving_key_pressed_count > 0 && map->IsWalkable(link->GetPositionLogic() + CGame::UNIT_VECS[direction]))
			{
				link->UpdateState(CCharacter::S_WALK, direction);
				target_position_render = link->GetPositionRender() + CGame::UNIT_VECS[direction] * MAP_TILE_SIZE;
			}
		}

		/* 移动状态 */
		if (link->GetState() == CCharacter::S_WALK)
		{
			unsigned tick = clock();
			while (!link->GetPositionRender().NearlyEqual(target_position_render))
			{
				if (clock() - tick >= CGame::ONE_SEC / CGame::FPS)
				{
					link->MoveRender(UNIT_VECS[link->GetDirection()] * link->GetVelocity());
					CGraphic::GetInstance()->BeginDraw();
					map->Draw();
					link->Draw();
					CGraphic::GetInstance()->EndDraw();
					tick = clock();
					CGame::CheckMessageQuit(msg);
				}
			}
			link->MoveLogic(UNIT_VECS[link->GetDirection()]);

			CActor::Direction direction = link->GetDirection();
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
			link->UpdateState(CCharacter::S_IDLE, direction);
			if (m_moving_key_pressed_count > 0 && map->IsWalkable(link->GetPositionLogic() + CGame::UNIT_VECS[direction]))
			{
				link->UpdateState(CCharacter::S_WALK, direction);
				target_position_render = link->GetPositionRender() + CGame::UNIT_VECS[direction] * MAP_TILE_SIZE;
			}
		}
	}

	delete link;
	delete map;

	return 0;
}
