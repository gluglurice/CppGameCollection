#pragma once

#include <Singleton.h>

#include "Door.h"

class CDoorFC : public CSingleton<CDoorFC>
{
	friend CSingleton<CDoorFC>;

protected:
	map<int, CDoor*> m_door_map;

	CDoorFC();

public:
	~CDoorFC();

	CDoor* CreateDoor(CVector3D position_logic, CDoor::Type type, bool is_open);
};
