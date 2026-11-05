#include "CCppGameCollection.h"

CCppGameCollection::CCppGameCollection() {}

CCppGameCollection::~CCppGameCollection() {}

void CCppGameCollection::Run()
{
	CSokobanV2 sokoban;
	sokoban.RunGame();
}
