#pragma once

#include <Graphic.h>
#include <Vector3D.h>

class CGame : public CSingleton<CGame>
{
	/**
	 * @brief 友元化基类，便于基类指针调用派生类私有构造函数
	 */
	friend CSingleton<CGame>;

public:
	static const string GAME_INI_PATH;
	static const float ONE_SEC;

	static int GRAPH_WIDTH;
	static int GRAPH_HEIGHT;
	static int MAP_TILE_SIZE;
	static int FPS;
	static float SCALE;
	static vector<CVector3D> UNIT_VECS;

protected:
	/**
	 * @brief 按键状态
	 */
	static map<int, bool> m_key_pressed;

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
	bool CheckMessageQuit(MSG& msg);

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
