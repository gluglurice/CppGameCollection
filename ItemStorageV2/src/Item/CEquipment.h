#pragma once

#include "CItem.h"

class CEquipment : public CItem
{
public:
	enum EEquipmentType
	{
		ET_WEAPON,
		ET_ACCESSORY_FLOWER,
		ET_ACCESSORY_FEATHER,
		ET_ACCESSORY_HOURGLASS,
		ET_ACCESSORY_CUP,
		ET_ACCESSORY_CROWN,
		ET_COUNT,
	};

GET_SET_FUN_DECLAR(EEquipmentType, m_equipment_type, EquipmentType)

public:
	CEquipment();

	CEquipment(int id, const std::string& name, EItemType item_type, EEquipmentType equipment_type, int hp, int mp, int atk, int def);

	~CEquipment();
};
