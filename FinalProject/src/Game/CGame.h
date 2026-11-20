#pragma once

#include <string>

class CGame
{
public:
	static const std::string GAME_INI_PATH;
	static const int ONE_SEC;
	static int GRAPH_WIDTH;
	static int GRAPH_HEIGHT;
	static int FPS;

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
