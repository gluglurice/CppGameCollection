#pragma once

#include <string>

class CGame
{
public:
	static const std::string GAME_INI_PATH;

public:
	CGame();

	~CGame();

	void Run();
};
