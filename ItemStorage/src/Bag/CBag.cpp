#include "CBag.h"

const int CBag::BAG_IMG_NUM = 3;
const std::wstring CBag::BAG_IMG_PATHS[CBag::BAG_IMG_NUM] = {
	L"assets/imgs/ui/bag.png",
	L"assets/imgs/ui/bag_cell.png",
	L"assets/imgs/ui/bag_chosen.png",
};
IMAGE CBag::BAG_IMGS[CBag::BAG_IMG_NUM];

const int CBag::EQUIPMENTS_IMG_NUM = 3;
const std::wstring CBag::EQUIPMENTS_IMG_PATHS[CBag::EQUIPMENTS_IMG_NUM] = {
	L"assets/imgs/ui/equipments.png",
	L"assets/imgs/ui/equipments_cell.png",
	L"assets/imgs/ui/equipments_chosen.png",
};
IMAGE CBag::EQUIPMENTS_IMGS[CBag::EQUIPMENTS_IMG_NUM];

const int CBag::DEFAULT_ITEM_ARRAY_SIZE = 14;
const int CBag::ITEM_ARRAY_WIDTH = 7;
const int CBag::ITEM_ARRAY_HEIGHT = 2;

void CBag::Init()
{
	for (int i = 0; i < BAG_IMG_NUM; ++i)
	{
		loadimage(&BAG_IMGS[i], BAG_IMG_PATHS[i].c_str());
	}
	for (int i = 0; i < EQUIPMENTS_IMG_NUM; ++i)
	{
		loadimage(&EQUIPMENTS_IMGS[i], EQUIPMENTS_IMG_PATHS[i].c_str());
	}
}

CBag::CBag()
	: m_item_array_size(CBag::DEFAULT_ITEM_ARRAY_SIZE),
	m_item_chosen_index(0),
	m_items_array(std::vector<CItem*>(m_item_array_size, nullptr)),
	m_equipment_chosen_index(-1),
	m_equipments_array({ nullptr }) {}

CBag::~CBag() {}

void CBag::AddItem(CItem* item)
{
	m_items[item->GetID()] = item;

	for (int i = 0; i < m_item_array_size; ++i)
	{
		if (m_items_array[i] == nullptr)
		{
			m_items_array[i] = item;
			break;
		}
	}
}

void CBag::RemoveItem(CItem* item)
{
	m_items.erase(item->GetID());

	for (int i = 0; i < m_item_array_size; ++i)
	{
		if (m_items_array[i] == item)
		{
			m_items_array[i] = nullptr;
			break;
		}
	}
}

void CBag::Equip(CEquipment* equipment)
{
	auto it = m_equipments.find(equipment->GetEquipmentType());
	if (it != m_equipments.end())
	{
		AddItem(it->second);
		UnEquip(equipment->GetEquipmentType());
	}
	m_equipments[equipment->GetEquipmentType()] = equipment;
	RemoveItem(equipment);

	m_equipments_array[static_cast<int>(equipment->GetEquipmentType())] = equipment;
}

void CBag::UnEquip(CEquipment::EEquipmentType equipment_type)
{
	auto it = m_equipments.find(equipment_type);
	if (it != m_equipments.end())
	{
		AddItem(it->second);
		m_equipments.erase(it);
	}

	m_equipments_array[static_cast<int>(equipment_type)] = nullptr;
}

void CBag::ChooseItem(int index)
{
	if (index >= 0 && index < m_item_array_size)
	{
		m_item_chosen_index = index;
	}
}

void CBag::ChooseEquipment(int index)
{
	if (index >= 0 && index < CEquipment::EEquipmentType::ET_COUNT - 1)
	{
		m_equipment_chosen_index = index;
	}
}

void CBag::Draw()
{
	putimage_alpha_zoom(200, 600, 1, &BAG_IMGS[0]);
	putimage_alpha_zoom(800, 0, 1, &EQUIPMENTS_IMGS[0]);

	/* 绘制物品 */
	for (int i = 0; i < m_item_array_size; ++i)
	{
		if (m_items_array[i] != nullptr)
		{
			CItem* item = m_items_array[i];
			switch (item->GetItemType())
			{
			case CItem::EItemType::IT_DRUG:
				putimage_alpha_zoom(213 + (i % 7) * 100, 618 + (i / 7) * 90, 0.9f, &CDrug::DRUG_IMGS[static_cast<int>(static_cast<CDrug*>(item)->GetDrugType())]);
				break;
			case CItem::EItemType::IT_EQUIPMENT:
				putimage_alpha_zoom(213 + (i % 7) * 100, 618 + (i / 7) * 90, 0.9f, &CEquipment::EQUIPMENT_IMGS[static_cast<int>(static_cast<CEquipment*>(item)->GetEquipmentType())]);
				break;
			default:
				break;
			}
		}
	}

	/* 绘制背包格子 */
	for (int i = 0; i < CBag::ITEM_ARRAY_HEIGHT; i++)
	{
		for (int j = 0; j < CBag::ITEM_ARRAY_WIDTH; j++)
		{
			if (i * 7 + j == m_item_chosen_index)
			{
				putimage_alpha_zoom(210 + j * 100, 615 + i * 90, 1, &BAG_IMGS[2]);
				continue;
			}
			putimage_alpha_zoom(210 + j * 100, 615 + i * 90, 1, &BAG_IMGS[1]);
		}
	}

	/* 绘制装备 */
	for (int i = 0; i < CEquipment::EEquipmentType::ET_COUNT; i++)
	{
		if (m_equipments_array[i] != nullptr)
		{
			putimage_alpha_zoom(810, 10 + i * 100, 1, &CEquipment::EQUIPMENT_IMGS[m_equipments_array[i]->GetEquipmentType()]);
		}
	}

	/* 绘制装备格子 */
	for (int i = 0; i < CEquipment::EEquipmentType::ET_COUNT; i++)
	{
		if (i == m_equipment_chosen_index)
		{
			putimage_alpha_zoom(810, 10 + i * 100, 1, &EQUIPMENTS_IMGS[2]);
			continue;
		}
		putimage_alpha_zoom(810, 10 + i * 100, 1, &EQUIPMENTS_IMGS[1]);
	}
}

GET_SET_FUN_DEFINE(ItemMap, CBag, m_items, Items)
GET_SET_FUN_DEFINE(EquipmentMap, CBag, m_equipments, Equipments)
GET_SET_FUN_DEFINE(int, CBag, m_item_array_size, ItemArraySize)
GET_SET_FUN_DEFINE(int, CBag, m_item_chosen_index, ItemChosenIndex)
GET_SET_FUN_DEFINE(ItemsArray, CBag, m_items_array, ItemsArray)
GET_SET_FUN_DEFINE(int, CBag, m_equipment_chosen_index, EquipmentChosenIndex)
GET_SET_FUN_DEFINE(EquipmentsArray, CBag, m_equipments_array, EquipmentsArray)
