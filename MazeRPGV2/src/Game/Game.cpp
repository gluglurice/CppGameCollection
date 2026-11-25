#include "Game.h"

#include <Sprite.h>

#include "Character.h"

#define PI 3.1415926

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

CGame::CGame() : CSingleton<CGame>() {}

int CGame::WinRun(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	auto hwnd = CGraphic::GetInstance()->InitWindow(&CGame::WndProc, 550, 414);
	CGraphic::GetInstance()->InitDX(hwnd);

	MSG msg;

	Image* img_background = new Image();
	CGraphic::GetInstance()->LoadTex(L"assets/img/background/level_0-1.png", *img_background);

	Image* img_character_idle = new Image();
	CGraphic::GetInstance()->LoadTex(L"assets/img/character/Link_idle.png", *img_character_idle);
	CSprite sprite_character_idle(img_character_idle, 3, 3);
	sprite_character_idle.SetReadMode(CSprite::RM_ONE_ROW, 1, 0, 1, 3);
	sprite_character_idle.SetDefaultDirection(CSprite::D_LEFT);
	sprite_character_idle.SetFrameTerminal(3);
	sprite_character_idle.SetCycleTerminal(200);

	Image* img_character_walk = new Image();
	CGraphic::GetInstance()->LoadTex(L"assets/img/character/Link_walk.png", *img_character_walk);
	CSprite sprite_character_walk(img_character_walk, 3, 10);
	sprite_character_walk.SetReadMode(CSprite::RM_ONE_ROW, 1, 0, 1, 10);
	sprite_character_walk.SetDefaultDirection(CSprite::D_LEFT);

	D3DXVECTOR3 center(12.0f, 11.0f, 0.0f);
	D3DXVECTOR3 pos(48.0f * 2, 280.0f, 0.0f);
	D3DXVECTOR3 rot(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 scale(2.0f, 2.0f, 2.0f);

	CCharacter character(center, pos, rot, scale, CCharacter::Direction::D_LEFT);
	character.AddSprite(CCharacter::S_IDLE, &sprite_character_idle);
	character.AddSprite(CCharacter::S_WALK, &sprite_character_walk);
	character.UpdateState(CCharacter::S_IDLE);

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
		character.Draw();
		CGraphic::GetInstance()->DrawTex(*img_background, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), scale);
		CGraphic::GetInstance()->EndDraw();

		if (m_key_pressed['A'].first)
		{
			if (!m_key_pressed['A'].second)
			{
				m_key_pressed['A'].second = true;
				m_key_pressed_count++;
				character.SetDirection(CCharacter::D_LEFT);
				character.UpdateState(CCharacter::S_WALK);
			}
			character.Move(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
		}
		if (m_key_pressed['D'].first)
		{
			if (!m_key_pressed['D'].second)
			{
				m_key_pressed['D'].second = true;
				m_key_pressed_count++;
				character.SetDirection(CCharacter::D_RIGHT);
				character.UpdateState(CCharacter::S_WALK);
			}
			character.Move(D3DXVECTOR3(1.0f, 0.0f, 0.0f));
		}
		if (m_key_pressed_count == 0)
		{
			if (character.GetState() != CCharacter::S_IDLE)
			{
				character.UpdateState(CCharacter::S_IDLE);
			}
			character.Idle();
		}
	}
	return 0;
}
