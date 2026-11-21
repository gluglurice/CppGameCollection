#pragma once

#include <map>
#include <string>

#include <EasyXExtension.h>

#include "src/Actor/CShip.h"

class IMAGE;

class CShipFC
{
private:
	static CShipFC* m_instance;

public:
	static CShipFC* GetInstance();

private:
	std::map<CShip::EShipType, std::pair<CShip*, IMAGE*>> m_ship_map;

private:
	CShipFC();

public:
	~CShipFC();

	IMAGE* GetImg(CShip::EShipType ship_type);

	CShip* CreateShip(const CVector3D& position, CShip::EShipCamp ship_camp, CShip::EShipType ship_type);
};
