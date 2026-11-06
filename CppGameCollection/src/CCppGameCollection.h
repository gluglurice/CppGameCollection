#pragma once

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

class CCppGameCollection
{
public:
	CCppGameCollection();

	~CCppGameCollection();

	void Run();
};
