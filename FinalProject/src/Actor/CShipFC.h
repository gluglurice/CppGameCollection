#pragma once

#include "src/Actor/CShip.h"

class CShipFC : public CSingleton<CShipFC>
{
	/**
	 * @brief 友元化基类，便于基类指针调用派生类私有构造函数
	 */
	friend CSingleton<CShipFC>;

protected:
	static map<CShip::EShipType, pair<CShip*, Image*>> m_ship_map;

	CShipFC();

public:
	Image* GetImg(CShip::EShipType ship_type);

	CShip* CreateShip(const CVector3D& position, CShip::EShipCamp ship_camp, CShip::EShipType ship_type);
};
