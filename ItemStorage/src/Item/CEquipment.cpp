#include "CEquipment.h"

const int CEquipment::EQUIPMENT_IMG_NUM = 6;
const std::wstring CEquipment::EQUIPMENT_IMG_PATHS[CEquipment::EQUIPMENT_IMG_NUM] = {
	L"assets/imgs/item/equipment_weapon.png",
	L"assets/imgs/item/equipment_accessory_flower.png",
	L"assets/imgs/item/equipment_accessory_feather.png",
	L"assets/imgs/item/equipment_accessory_hourglass.png",
	L"assets/imgs/item/equipment_accessory_cup.png",
	L"assets/imgs/item/equipment_accessory_crown.png",
};
IMAGE CEquipment::EQUIPMENT_IMGS[CEquipment::EQUIPMENT_IMG_NUM];

void CEquipment::Init()
{
	for (int i = 0; i < EQUIPMENT_IMG_NUM; ++i)
	{
		loadimage(&EQUIPMENT_IMGS[i], EQUIPMENT_IMG_PATHS[i].c_str());
	}
}

CEquipment::CEquipment() {}

CEquipment::CEquipment(int id, const std::string& name, EItemType item_type, EEquipmentType equipment_type, int hp, int mp, int atk, int def)
	: CItem(id, name, item_type, hp, mp, atk, def), m_equipment_type(equipment_type) {}

CEquipment::~CEquipment() {}

GET_SET_FUN_DEFINE(CEquipment::EEquipmentType, CEquipment, m_equipment_type, EquipmentType)
