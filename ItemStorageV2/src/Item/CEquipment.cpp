#include "CEquipment.h"

CEquipment::CEquipment() {}

CEquipment::CEquipment(int id, const std::string& name, EItemType item_type, EEquipmentType equipment_type, int hp, int mp, int atk, int def)
	: CItem(id, name, item_type, hp, mp, atk, def), m_equipment_type(equipment_type) {}

CEquipment::~CEquipment() {}

GET_SET_FUN_DEFINE(CEquipment::EEquipmentType, CEquipment, m_equipment_type, EquipmentType)
