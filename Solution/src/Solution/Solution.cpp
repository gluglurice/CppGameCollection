#include "Solution.h"

#include <Vector3D.h>

#define PI 3.1415926

map<int, pair<bool, bool>> CSolution::m_key_pressed = {
	{ 'W', make_pair(false, false) },
	{ 'A', make_pair(false, false) },
	{ 'S', make_pair(false, false) },
	{ 'D', make_pair(false, false) },
	{ 'Q', make_pair(false, false) },
	{ 'E', make_pair(false, false) },
	{ 'F', make_pair(false, false) },
	{ 'Z', make_pair(false, false) },
	{ 'C', make_pair(false, false) },
};

CSolution::CSolution() : CSingleton<CSolution>() {}

LRESULT CSolution::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

int CSolution::WinRun(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	auto hwnd = CGraphic::GetInstance()->InitWindow(&CSolution::WndProc, 1024, 786);
	CGraphic::GetInstance()->InitDX(hwnd);

	MSG msg;

	Image img;
	CGraphic::GetInstance()->LoadTex(L"assets/role.png", img);
	CVector3D center(300.0f, 300.0f, 0.0f);
	CVector3D pos(512.0f, 393.0f, 0.0f);
	CVector3D rot(0.0f, 0.0f, 0.0f);
	CVector3D scale(1.0f, 1.0f, 1.0f);

	while (true)
	{ 
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		CGraphic::GetInstance()->BeginDraw();

		CGraphic::GetInstance()->DrawTex(img, pos, center, rot, scale);

		CGraphic::GetInstance()->SetFont(20);
		CGraphic::GetInstance()->DrawTextW(
			L"WASD：移动",
			{ 10, 10, 300, 50 },
			DT_LEFT | DT_TOP,
			D3DCOLOR_RGBA(90, 253, 254, 255));
		CGraphic::GetInstance()->DrawTextW(
			L"QE：旋转",
			{ 10, 60, 300, 100 },
			DT_LEFT | DT_TOP,
			D3DCOLOR_RGBA(90, 253, 254, 255));
		CGraphic::GetInstance()->DrawTextW(
			L"ZC：缩放",
			{ 10, 110, 300, 150 },
			DT_LEFT | DT_TOP,
			D3DCOLOR_RGBA(90, 253, 254, 255));
		CGraphic::GetInstance()->DrawTextW(
			L"F：水平翻转",
			{ 10, 160, 300, 200 },
			DT_LEFT | DT_TOP,
			D3DCOLOR_RGBA(90, 253, 254, 255));

		/* 移动 */
		if (CSolution::m_key_pressed['W'].first)
		{
			pos.y -= 1.0f;
		}
		if (CSolution::m_key_pressed['S'].first)
		{
			pos.y += 1.0f;
		}
		if (CSolution::m_key_pressed['A'].first)
		{
			pos.x -= 1.0f;
		}
		if (CSolution::m_key_pressed['D'].first)
		{
			pos.x += 1.0f;
		}

		/* 旋转 */
		if (CSolution::m_key_pressed['Q'].first)
		{
			rot.z -= PI / 180.0f;
		}
		if (CSolution::m_key_pressed['E'].first)
		{
			rot.z += PI / 180.0f;
		}

		/* 缩放 */
		if (CSolution::m_key_pressed['Z'].first)
		{
			scale.x = (scale.x / abs(scale.x)) * (abs(scale.x) - 0.01f);
			scale.y -= 0.01f;
		}
		if (CSolution::m_key_pressed['C'].first)
		{
			scale.x = (scale.x / abs(scale.x)) * (abs(scale.x) + 0.01f);
			scale.y += 0.01f;
		}

		/* 水平翻转 */
		if (CSolution::m_key_pressed['F'].first)
		{
			if (!CSolution::m_key_pressed['F'].second)
			{
				scale.x *= -1;

				CSolution::m_key_pressed['F'].second = true;
			}
		}

		CGraphic::GetInstance()->EndDraw();
	}
	return 0;
}
