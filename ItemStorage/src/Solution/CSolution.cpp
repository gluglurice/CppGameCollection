#include "CSolution.h"

#include <iostream>

#include <conio.h>
#include <graphics.h>

#include "src/Role/CRole.h"
#include "src/Item/CItem.h"
#include "src/Item/CEquipment.h"
#include "src/Item/CDrug.h"

CSolution::CSolution() {}

CSolution::~CSolution() {}

void CSolution::Run()
{
	CRole::Init();
	CBag::Init();
	CEquipment::Init();
	CDrug::Init();

	CItem* drug_heal = new CDrug(1001, "Health Potion", CItem::IT_DRUG, CDrug::DT_HEAL, 500, 0, 0, 0);
	CItem* drug_mana = new CDrug(1002, "Mana Potion", CItem::IT_DRUG, CDrug::DT_MANA, 0, 500, 0, 0);
	CItem* drug_buff_atk = new CDrug(1003, "Strength Potion", CItem::IT_DRUG, CDrug::DT_BUFF_ATK, 0, 0, 200, 0);
	CItem* drug_buff_def = new CDrug(1004, "Defense Potion", CItem::IT_DRUG, CDrug::DT_BUFF_DEF, 0, 0, 0, 200);

	CItem* equipment_weapon = new CEquipment(2001, "Sword", CItem::IT_EQUIPMENT, CEquipment::ET_WEAPON, 0, 0, 1000, 0);
	CItem* equipment_accessory_flower = new CEquipment(2002, "Flower", CItem::IT_EQUIPMENT, CEquipment::ET_ACCESSORY_FLOWER, 2000, 0, 0, 0);
	CItem* equipment_accessory_feather = new CEquipment(2003, "Feather", CItem::IT_EQUIPMENT, CEquipment::ET_ACCESSORY_FEATHER, 0, 0, 1000, 0);
	CItem* equipment_accessory_hourglass = new CEquipment(2004, "Hourglass", CItem::IT_EQUIPMENT, CEquipment::ET_ACCESSORY_HOURGLASS, 500, 500, 0, 0);
	CItem* equipment_accessory_cup = new CEquipment(2005, "Cup", CItem::IT_EQUIPMENT, CEquipment::ET_ACCESSORY_CUP, 500, 0, 500, 0);
	CItem* equipment_accessory_crown = new CEquipment(2006, "Crown", CItem::IT_EQUIPMENT, CEquipment::ET_ACCESSORY_CROWN, 500, 0, 0, 500);

	CRole role("桑多涅", 800, 1000, 800, 1000, 100, 100);

	role.AddItem(drug_heal);
	role.AddItem(drug_mana);
	role.AddItem(drug_buff_atk);
	role.AddItem(drug_buff_def);

	role.AddItem(equipment_weapon);
	role.AddItem(equipment_accessory_flower);
	role.AddItem(equipment_accessory_feather);
	role.AddItem(equipment_accessory_hourglass);
	role.AddItem(equipment_accessory_cup);
	role.AddItem(equipment_accessory_crown);

	initgraph(900, 800);

	int item_x = role.GetBag().GetItemChosenIndex() % CBag::ITEM_ARRAY_WIDTH;
	int item_y = role.GetBag().GetItemChosenIndex() / CBag::ITEM_ARRAY_WIDTH;
	int equipment_y = role.GetBag().GetEquipmentChosenIndex() % CEquipment::EEquipmentType::ET_COUNT;

	while (true)
	{
		BeginBatchDraw();

		role.Draw();

		if (_kbhit())
		{
			char key = _getch();
			switch (key)
			{
			case 'w':
			case 'W':
				if (item_y > 0)
				{
					item_y--;
					role.ChooseItem(item_y * CBag::ITEM_ARRAY_WIDTH + item_x);
				}
				else if (item_y == 0)
				{
					item_x = -1;
					item_y = -1;
					equipment_y = CEquipment::EEquipmentType::ET_COUNT - 1;
					role.ChooseItem(-1);
					role.ChooseEquipment(equipment_y);
				}
				else if (equipment_y > 0)
				{
					equipment_y--;
					role.ChooseEquipment(equipment_y);
				}
				break;
			case 's':
			case 'S':
				if (equipment_y >= 0 && equipment_y < CEquipment::EEquipmentType::ET_COUNT - 1)
				{
					equipment_y++;
					role.ChooseEquipment(equipment_y);
				}
				else if (equipment_y == CEquipment::EEquipmentType::ET_COUNT - 1)
				{
					item_x = CBag::ITEM_ARRAY_WIDTH - 1;
					item_y = 0;
					equipment_y = -1;
					role.ChooseEquipment(-1);
					role.ChooseItem(item_y * CBag::ITEM_ARRAY_WIDTH + item_x);
				}
				else if (item_y < CBag::ITEM_ARRAY_HEIGHT - 1)
				{
					item_y++;
					role.ChooseItem(item_y * CBag::ITEM_ARRAY_WIDTH + item_x);
				}
				break;
			case 'a':
			case 'A':
				if (item_x > 0)
				{
					item_x--;
					role.ChooseItem(item_y * CBag::ITEM_ARRAY_WIDTH + item_x);
				}
				break;
			case 'd':
			case 'D':
				if (item_x < CBag::ITEM_ARRAY_WIDTH - 1)
				{
					item_x++;
					role.ChooseItem(item_y * CBag::ITEM_ARRAY_WIDTH + item_x);
				}
				break;
			case ' ':
				if (item_x >= 0 && item_y >= 0)
				{
					CItem* item = role.GetBag().GetItemsArray()[item_y * CBag::ITEM_ARRAY_WIDTH + item_x];
					if (item != nullptr)
					{
						switch (item->GetItemType())
						{
						case CItem::EItemType::IT_DRUG:
							role.UseDrug(static_cast<CDrug*>(item));
							break;
						case CItem::EItemType::IT_EQUIPMENT:
							role.Equip(static_cast<CEquipment*>(item));
							break;
						default:
							break;
						}
					}
				}
				else if (equipment_y >= 0)
				{
					CEquipment* equipment = role.GetBag().GetEquipments()[static_cast<CEquipment::EEquipmentType>(equipment_y)];
					if (equipment != nullptr)
					{
						role.UnEquip(static_cast<CEquipment::EEquipmentType>(equipment_y));
					}
				}
				break;
			}
		}
		EndBatchDraw();
	}

	_getch();
	closegraph();
}
