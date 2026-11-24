#pragma once

#include <Graphic.h>

class CGame : public CSingleton<CGame>
{
	/**
	 * @brief 友元化基类，便于基类指针调用派生类私有构造函数
	 */
	friend CSingleton<CGame>;

protected:
	/**
	 * @brief 按键状态，first表示按下，second表示按下后是否处理过
	 */
	static map<int, pair<bool, bool>> m_key_pressed;

	static unsigned m_key_pressed_count;

	/**
	 * @brief 窗口消息回调
	 * @param hwnd 
	 * @param msg 
	 * @param wParam 
	 * @param lParam 
	 * @return 
	 */
	static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	/**
	 * @brief 单例类私有构造函数
	 */
	CGame();

public:
	/**
	 * @brief 窗口运行入口
	 * @param hInstance 
	 * @param hPrevInstance 
	 * @param lpCmdLine 
	 * @param nShowCmd 
	 * @return 
	 */
	int WinRun(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd);
};
