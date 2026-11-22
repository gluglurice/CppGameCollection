#pragma once

#include <Graphic.h>
#include <Singleton.h>

class CSolution : public CSingleton<CSolution>
{
	friend CSingleton<CSolution>;

public:
	/**
	 * @brief 按键状态，first表示按下，second表示按下后是否处理过
	 */
	static map<int, pair<bool, bool>> m_key_pressed;

	static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	CSolution();

public:
	int WinRun(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd);
};
