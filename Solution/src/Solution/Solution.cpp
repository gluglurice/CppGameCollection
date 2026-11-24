#include "Solution.h"

#include <Sprite.h>

#define PI 3.1415926

map<int, pair<bool, bool>> CSolution::m_key_pressed = {
	{ 'W', make_pair(false, false) },
	{ 'A', make_pair(false, false) },
	{ 'S', make_pair(false, false) },
	{ 'D', make_pair(false, false) },
};

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

CSolution::CSolution() : CSingleton<CSolution>() {}

int CSolution::WinRun(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	auto hwnd = CGraphic::GetInstance()->InitWindow(&CSolution::WndProc, 1216, 207);
	CGraphic::GetInstance()->InitDX(hwnd);

	MSG msg;

	Image* img_background = new Image();
	CGraphic::GetInstance()->LoadTex(L"assets/level_0-1.png", *img_background);

	Image* img_character = new Image();
	CGraphic::GetInstance()->LoadTex(L"assets/character_walk.png", *img_character);
	D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 pos(10.0f, 124.0f, 0.0f);
	D3DXVECTOR3 rot(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 scale(1.0f, 1.0f, 1.0f);

	CSprite sprite_character(img_character, 1, 10, center, pos, rot, scale);
	sprite_character.SetPlayState(CSprite::PS_CYCLE);
	sprite_character.SetFrameTerminal(10);

	while (true)
	{ 
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		CGraphic::GetInstance()->BeginDraw();

		sprite_character.Update();
		sprite_character.Draw();

		CGraphic::GetInstance()->DrawTex(*img_background, D3DXVECTOR3(0, 0, 0));

		CGraphic::GetInstance()->EndDraw();
	}
	return 0;
}
