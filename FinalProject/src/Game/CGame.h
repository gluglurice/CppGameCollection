#pragma once

#include <string>

class CGame
{
public:
	static const std::string GAME_INI_PATH;

	static void Init();

	static void Delete();

public:
	CGame();

	~CGame();

	void Run();
};
