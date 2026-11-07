#include "CSolution.h"

#include "Hero/CHero.h"
#include "Hero/CMasterYi.h"
#include "Hero/CNasus.h"
#include "Hero/CMissFortune.h"

CSolution::CSolution() {}

CSolution::~CSolution() {}

void CSolution::Run()
{
	TestHeroSay();
}

void CSolution::TestHeroSay()
{
	CHero* masterYi = new CMasterYi();
	CHero* nasus = new CNasus();
	CHero* missFortune = new CMissFortune();

	masterYi->Say();
	nasus->Say();
	missFortune->Say();

	system("pause");

	delete masterYi;
	delete nasus;
	delete missFortune;
}
