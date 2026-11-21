#pragma once

#include <string>

class CGame
{
public:
	static const std::string GAME_INI_PATH;
	static const unsigned ONE_SEC;
	static unsigned GRAPH_WIDTH;
	static unsigned GRAPH_HEIGHT;
	static unsigned FPS;

private:
	static CGame* m_instance;

public:
	static CGame* GetInstance();

private:
	CGame();

public:
	~CGame();

	void Run();
};
