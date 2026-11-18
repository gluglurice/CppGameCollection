#include "Game/CGame.h"

int main()
{
	CGame::Init();
	CGame game;
	game.Run();
	CGame::Delete();
	return 0;
}