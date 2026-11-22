#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <set>	
#include <map>
#include <string>

#include <conio.h>
#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <tinyxml.h>
#include <Singleton.h>

using namespace std;

#ifdef _UNICODE
#define TSTRING wstring
#define TCOUT wcout
#else
#define TSTRING string
#define TCOUT cout
#endif

struct Image
{
	LPDIRECT3DTEXTURE9 pTex; 
	WORD width;
	WORD height;
};

typedef LRESULT (CALLBACK *pMainWndProc)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CGraphic : public CSingleton<CGraphic>
{
    friend CSingleton<CGraphic>;

public:
	HWND InitWindow(pMainWndProc proc, WORD width=800, WORD height=600, TSTRING titelName=_T("Game"), TSTRING className=_T("MyClass"));

	void InitDX(HWND hwnd);
	void CloseDX();

	void BeginDraw();
	void EndDraw();

	HRESULT LoadTex(LPCTSTR fileName, Image& info, DWORD color = 0xff000000);
	void SetFont(int w, int h = 0, const wchar_t* fontFaimly = L"宋体");
	void DrawTex(LPDIRECT3DTEXTURE9 tex, D3DXVECTOR2 srcPos, D3DXVECTOR2 size, D3DXVECTOR3 pos, D3DXVECTOR3 center = D3DXVECTOR3(0.0f, 0, 0), D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0, 0), D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1, 1));
	void DrawTex(Image& info, D3DXVECTOR3 pos, D3DXVECTOR3 center = D3DXVECTOR3(0.0f, 0, 0), D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0, 0), D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1, 1));
	void DrawTex(Image& info, D3DXVECTOR3 center,D3DXMATRIX matWorld);
	void DrawText(TSTRING text, RECT rc, DWORD style=DT_LEFT|DT_TOP, DWORD color=0xffff0000);
	void DrawLine(D3DXVECTOR3 start, D3DXVECTOR3 end, DWORD color = 0xffff0000);
	void DrawNumber(D3DXVECTOR3 pos, int num);

	LPDIRECT3DDEVICE9 m_pDevice;
	HWND m_hMainWnd;

private:
	LPDIRECT3DTEXTURE9 m_pTex;
	IDirect3D9* m_pD3D;
	
	LPD3DXLINE m_pLine;
	LPD3DXSPRITE m_pSprite;
	LPD3DXFONT m_pFont;
};
