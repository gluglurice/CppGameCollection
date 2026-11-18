#pragma once

#include <array>
#include <vector>
#include <map>
#include <string>

#include <Utils/Utils.h>

#include "src/Item/CItem.h"
#include "src/Item/CItemFC.h"
#include "src/Item/CDrug.h"
#include "src/Item/CEquipment.h"

class CRole;

using ItemMap = std::map<int, CItem*>;
using EquipmentMap = std::map<CEquipment::EEquipmentType, CEquipment*>;
using ItemsArray = std::vector<CItem*>;
using EquipmentsArray = std::array<CEquipment*, CEquipment::EEquipmentType::ET_COUNT>;

class CBag
{
public:
	static const int BAG_IMG_NUM;
	static const std::wstring BAG_IMG_PATHS[];
	static IMAGE BAG_IMGS[];

	static const int EQUIPMENTS_IMG_NUM;
	static const std::wstring EQUIPMENTS_IMG_PATHS[];
	static IMAGE EQUIPMENTS_IMGS[];

	static const int DEFAULT_ITEM_ARRAY_SIZE;
	static const int ITEM_ARRAY_WIDTH;
	static const int ITEM_ARRAY_HEIGHT;

	static void Init();

GET_SET_FUN_DECLAR(ItemMap, m_items, Items)
GET_SET_FUN_DECLAR(EquipmentMap, m_equipments, Equipments)
GET_SET_FUN_DECLAR(int, m_item_array_size, ItemArraySize)
GET_SET_FUN_DECLAR(int, m_item_chosen_index, ItemChosenIndex)
GET_SET_FUN_DECLAR(ItemsArray, m_items_array, ItemsArray)
GET_SET_FUN_DECLAR(int, m_equipment_chosen_index, EquipmentChosenIndex)
GET_SET_FUN_DECLAR(EquipmentsArray, m_equipments_array, EquipmentsArray)

public:
	CBag();

	~CBag();

	void AddItem(CItem* item);

	void RemoveItem(CItem* item);

	void Equip(CEquipment* equipment, CRole* role);

	void UnEquip(CEquipment::EEquipmentType equipment_type, CRole* role);

	void ChooseItem(int index);

	void ChooseEquipment(int index);

	void Draw();
};
