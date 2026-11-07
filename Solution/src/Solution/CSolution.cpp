#include "CSolution.h"

#include "src/Hero/CHero.h"
#include "src/Hero/CMasterYi.h"
#include "src/Hero/CNasus.h"
#include "src/Hero/CMissFortune.h"

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
