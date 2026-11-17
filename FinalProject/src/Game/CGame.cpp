#include "CGame.h"

#include <iostream>

#include "src/Actor/CShip.h"

CGame::CGame() {}

CGame::~CGame() {}

void CGame::Run()
{
	CShip ship(CActor::Position(0.0f, 0.0f), CShip::ST_ENEMY);
	std::cout << "Ship Type: " << ship.GetShipType() << std::endl;
	std::cout << "Ship Angle: " << ship.GetAngleDegrees() << std::endl;
	std::cout << "Ship Velocity: " << ship.GetVelocity() << std::endl;
}
