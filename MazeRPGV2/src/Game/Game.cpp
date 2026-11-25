#include "Game.h"

#include <Sprite.h>

#include "Map.h"
#include "MapFC.h"
#include "Character.h"
#include "CharacterFC.h"

#define PI 3.1415926

const string CGame::GAME_INI_PATH = "config/game_ini.xml";

int CGame::GRAPH_WIDTH;
int CGame::GRAPH_HEIGHT;
int CGame::FPS;

map<int, pair<bool, bool>> CGame::m_key_pressed = {
	{ 'W', make_pair(false, false) },
	{ 'A', make_pair(false, false) },
	{ 'S', make_pair(false, false) },
	{ 'D', make_pair(false, false) },
};

unsigned CGame::m_key_pressed_count = 0;

LRESULT CGame::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		m_key_pressed[wParam].first = true;
		break;
	case WM_KEYUP:
		m_key_pressed[wParam].first = false;
		m_key_pressed[wParam].second = false;
		m_key_pressed_count = m_key_pressed_count > 0 ? m_key_pressed_count - 1 : 0;
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

	/* 初始化窗口 */
	auto hwnd = CGraphic::GetInstance()->InitWindow(&CGame::WndProc, CGame::GRAPH_WIDTH, CGame::GRAPH_HEIGHT);
	CGraphic::GetInstance()->InitDX(hwnd);
}

int CGame::WinRun(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	MSG msg;

	CMap* map = CMapFC::GetInstance()->CreateLevelMap(0);

	CCharacter* link = CCharacterFC::GetInstance()->CreateCharacter(D3DXVECTOR3(96.0f, 280.0f, 0.0f), CCharacter::T_PLAYER);
	link->UpdateState(CCharacter::S_IDLE, CActor::D_DOWN);

	while (true)
	{ 
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		CGraphic::GetInstance()->BeginDraw();
		link->Draw();
		map->Draw();
		CGraphic::GetInstance()->EndDraw();

		if (m_key_pressed['W'].first)
		{
			if (!m_key_pressed['W'].second)
			{
				m_key_pressed['W'].second = true;
				m_key_pressed_count++;
				link->UpdateState(CCharacter::S_WALK, CActor::D_UP);
			}
			link->Move(CCharacter::D_UP);
		}
		if (m_key_pressed['S'].first)
		{
			if (!m_key_pressed['S'].second)
			{
				m_key_pressed['S'].second = true;
				m_key_pressed_count++;
				link->UpdateState(CCharacter::S_WALK, CActor::D_DOWN);
			}
			link->Move(CCharacter::D_DOWN);
		}
		if (m_key_pressed['A'].first)
		{
			if (!m_key_pressed['A'].second)
			{
				m_key_pressed['A'].second = true;
				m_key_pressed_count++;
				link->UpdateState(CCharacter::S_WALK, CActor::D_LEFT);
			}
			link->Move(CCharacter::D_LEFT);
		}
		if (m_key_pressed['D'].first)
		{
			if (!m_key_pressed['D'].second)
			{
				m_key_pressed['D'].second = true;
				m_key_pressed_count++;
				link->UpdateState(CCharacter::S_WALK, CActor::D_RIGHT);
			}
			link->Move(CCharacter::D_RIGHT);
		}
		if (m_key_pressed_count == 0)
		{
			if (link->GetState() != CCharacter::S_IDLE)
			{
				link->UpdateState(CCharacter::S_IDLE, link->GetDirection());
			}
			link->Idle();
		}
	}
	return 0;
}
