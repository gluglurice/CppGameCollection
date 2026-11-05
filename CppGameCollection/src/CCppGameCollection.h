#pragma once

#include "CSolution.h"
#include "DrawDiamond/DrawDiamond.h"
#include "NumBomb/NumBomb.h"
#include "RockPaperScissors/RockPaperScissors.h"
#include "Sokoban/Sokoban.h"
#include "SokobanV2/CSokobanV2.h"
#include "Gacha/Gacha.h"
#include "MazeRPG/MazeRPG.h"
#include "RPGBattle/CRPGBattle.h"
#include "GluttonousSnake/GluttonousSnake.h"
#include "Tetris/Tetris.h"

class CCppGameCollection
{
public:
	CCppGameCollection();

	~CCppGameCollection();

	void Run();
};
