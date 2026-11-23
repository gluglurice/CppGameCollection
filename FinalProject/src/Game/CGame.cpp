#include "CGame.h"

#include "CActor.h"
#include "CShip.h"
#include "CShipFC.h"
#include "CNormalBullet.h"
#include "CNormalBulletFC.h"
#include "CBomb.h"
#include "CItem.h"

#define PI 3.1415926
#define ONE_SEC 1000

unsigned CGame::GRAPH_WIDTH;
unsigned CGame::GRAPH_HEIGHT;
unsigned CGame::FPS;

map<int, pair<bool, bool>> CGame::m_key_pressed = {
	{ 'W', make_pair(false, false) },
	{ 'A', make_pair(false, false) },
	{ 'S', make_pair(false, false) },
	{ 'D', make_pair(false, false) },
};

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
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

CGame::CGame()
{
	TiXmlDocument xml_doc;
	if (!xml_doc.LoadFile(GAME_INI_PATH))
	{
		cerr << "读取游戏配置文件失败：" << GAME_INI_PATH << endl;
		return;
	}

	TiXmlElement* xml_root = xml_doc.RootElement();
	xml_root->QueryUnsignedAttribute("graph_width", &GRAPH_WIDTH);
	xml_root->QueryUnsignedAttribute("graph_height", &GRAPH_HEIGHT);
	xml_root->QueryUnsignedAttribute("fps", &FPS);
}

int CGame::WinRun(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	auto hwnd = CGraphic::GetInstance()->InitWindow(&CGame::WndProc, GRAPH_WIDTH, GRAPH_HEIGHT);
	CGraphic::GetInstance()->InitDX(hwnd);

	MSG msg;

	CShip* ship = CShipFC::GetInstance()->CreateShip(CVector3D(CGame::GRAPH_WIDTH / 2.0f, CGame::GRAPH_HEIGHT - 50.0f, 0.0f), CShip::EShipCamp::SC_PLAYER, CShip::EShipType::ST_BLUE_S);

	Image background;
	CGraphic::GetInstance()->LoadTex(L"assets/img/background.jpg" , background);

	static unsigned tick_ship_shoot = clock();
	static unsigned tick_bullet_move = clock();

	while (true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		CGraphic::GetInstance()->BeginDraw();
		ship->Draw();
		CGraphic::GetInstance()->DrawTex(background, CVector3D(0, 0, 0));
		CGraphic::GetInstance()->EndDraw();

		if (clock() - tick_ship_shoot > ONE_SEC / ship->GetFiringRate())
		{
			ship->Shoot();
			tick_ship_shoot = clock();
		}

		if (clock() - tick_bullet_move > ONE_SEC / CGame::FPS)
		{
			for (CNormalBullet* bullet : ship->GetNormalBullets())
			{
				bullet->Move(CVector3D(0, -bullet->GetVelocity(), 0));
			}
			tick_bullet_move = clock();
		}

		if (m_key_pressed['W'].first)
		{
			ship->Move(CVector3D(0, -ship->GetVelocity(), 0));
		}
		if (m_key_pressed['S'].first)
		{
			ship->Move(CVector3D(0, ship->GetVelocity(), 0));
		}
		if (m_key_pressed['A'].first)
		{
			ship->Move(CVector3D(-ship->GetVelocity(), 0, 0));
		}
		if (m_key_pressed['D'].first)
		{
			ship->Move(CVector3D(ship->GetVelocity(), 0, 0));
		}

		ship->CheckAndDestroyNormalBullets();
	}

	return 0;
}
