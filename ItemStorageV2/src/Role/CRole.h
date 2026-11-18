#pragma once

#include <string>

#include <Utils/Utils.h>

#include "src/Bag/CBag.h"
#include "src/Item/CEquipment.h"
#include "src/Item/CDrug.h"

class CRole
{
public:
	static const int ROLE_IMG_NUM;
	static const std::wstring ROLE_IMG_PATHS[];
	static IMAGE ROLE_IMGS[];

	static const int ATTRIBUTE_IMG_NUM;
	static const std::wstring ATTRIBUTE_IMG_PATHS[];
	static IMAGE ATTRIBUTE_IMGS[];

	static const int UI_IMG_NUM;
	static const std::wstring UI_IMG_PATHS[];
	static IMAGE UI_IMGS[];

	static void Init();

GET_SET_FUN_DECLAR(CBag, m_bag, Bag)
GET_SET_FUN_DECLAR(int, m_hp, HP)
GET_SET_FUN_DECLAR(int, m_max_hp, MaxHP)
GET_SET_FUN_DECLAR(int, m_mp, MP)
GET_SET_FUN_DECLAR(int, m_max_mp, MaxMP)
GET_SET_FUN_DECLAR(int, m_atk, ATK)
GET_SET_FUN_DECLAR(int, m_def, DEF)
GET_SET_FUN_DECLAR(std::string, m_name, Name)

public:
	CRole();

	CRole(const std::string& name, int hp, int max_hp, int mp, int max_mp, int atk, int def);

	~CRole();

	void AddItem(CItem* item);

	void RemoveItem(CItem* item);

	void UseDrug(CDrug* drug);

	void Equip(CEquipment* equipment);

	void UnEquip(CEquipment::EEquipmentType equipment_type);

	void ChooseItem(int index);

	void ChooseEquipment(int index);

	void Draw();
};
