#include "CGame.h"

#include <iostream>

#include "src/Actor/CActor.h"
#include "src/Actor/CShip.h"
#include "src/Actor/CNormalBullet.h"
#include "src/Actor/CBomb.h"
#include "src/Actor/CItem.h"

const std::string CGame::GAME_INI_PATH = "config/game_ini.xml";

void CGame::Init()
{
	CActor::Init(CGame::GAME_INI_PATH);
	CShip::Init(CGame::GAME_INI_PATH);
	CNormalBullet::Init(CGame::GAME_INI_PATH);
	CBomb::Init(CGame::GAME_INI_PATH);
	CItem::Init(CGame::GAME_INI_PATH);
}

void CGame::Delete()
{
	CActor::Delete();
	CShip::Delete();
	CNormalBullet::Delete();
	CBomb::Delete();
	CItem::Delete();
}

CGame::CGame() {}

CGame::~CGame() {}

void CGame::Run()
{

}
