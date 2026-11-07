#include "CCppGameCollection.h"

#include "Solution/CSolution.h"

#include "DrawDiamond/DrawDiamond.h"
#include "NumBomb/NumBomb.h"
#include "RockPaperScissors/RockPaperScissors.h"
#include "Sokoban/Sokoban.h"
#include "Gacha/Gacha.h"
#include "MazeRPG/MazeRPG.h"
#include "GluttonousSnake/GluttonousSnake.h"
#include "Tetris/Tetris.h"

#include "RPGBattle/CRPGBattle.h"
#include "SokobanV2/CSokobanV2.h"

CCppGameCollection::CCppGameCollection() {}

CCppGameCollection::~CCppGameCollection() {}

void CCppGameCollection::Run()
{
	CSolution solution;
	solution.Run();
}
