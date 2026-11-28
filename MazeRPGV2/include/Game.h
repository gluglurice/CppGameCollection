#pragma once

#include <Graphic.h>
#include <Vector3D.h>

class CMap;
class CCharacter;

class CGame : public CSingleton<CGame>
{
	friend CSingleton<CGame>;

public:
	static const string GAME_INI_PATH;
	static const float ONE_SEC;

	static int GRAPH_WIDTH;
	static int GRAPH_HEIGHT;
	static int MAP_TILE_SIZE;
	static int FPS;
	static float DELTA_TIME;
	static float SCALE;
	static vector<CVector3D> UNIT_VECS;

protected:
	static map<int, vector<bool>> m_key_pressed;
	static unsigned m_moving_key_pressed_count;

	MSG m_msg;
	bool m_is_game_quit;
	int m_level;
	CMap* m_map;
	CCharacter* m_character;

	static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	CGame();

public:
	void CheckMessage();
	void ListenLevelChangeEvent();
	void ListenCharacterIdleEvent();
	void ListenCharacterMoveEvent();
	void ListenDoorOpenEvent();
	void Update();
	void Draw();
	int WinRun(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd);
};
