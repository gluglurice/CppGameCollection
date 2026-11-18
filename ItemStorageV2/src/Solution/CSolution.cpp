#include "CSolution.h"

#include <iostream>

#include <conio.h>
#include <graphics.h>
#include <tinyxml/tinyxml.h>

#include "src/Role/CRole.h"
#include "src/Item/CItemFC.h"
#include "src/Item/CItem.h"
#include "src/Item/CEquipment.h"
#include "src/Item/CDrug.h"

const std::string CSolution::INI_XML_PATH = "config/ini.xml";
const std::string CSolution::SAVE_XML_PATH = "config/save.xml";
const std::string CSolution::XML_ENCODING = "ANSI";

CSolution::CSolution() {}

CSolution::~CSolution() {}

void CSolution::Init()
{
	CRole::Init();
	CBag::Init();
	CItemFC::GetInstance();
}

void CSolution::SaveXml(CRole& role)
{
	TiXmlDocument xml_doc;

	TiXmlElement* xml_root = new TiXmlElement("Save");

	TiXmlElement* xml_role = new TiXmlElement("Role");

	xml_role->SetAttribute("hp", role.GetHP());
	xml_role->SetAttribute("max_hp", role.GetMaxHP());
	xml_role->SetAttribute("mp", role.GetMP());
	xml_role->SetAttribute("max_mp", role.GetMaxMP());
	xml_role->SetAttribute("atk", role.GetATK());
	xml_role->SetAttribute("def", role.GetDEF());
	xml_role->SetAttribute("name", role.GetName().c_str());

	TiXmlElement* xml_bag = new TiXmlElement("Bag");

	xml_bag->SetAttribute("item_array_size", role.GetBag().GetItemArraySize());
	xml_bag->SetAttribute("item_chosen_index", role.GetBag().GetItemChosenIndex());
	xml_bag->SetAttribute("equipment_chosen_index", role.GetBag().GetEquipmentChosenIndex());

	for (const auto& item : role.GetBag().GetItems())
	{
		TiXmlElement* xml_item = new TiXmlElement("Item");
		xml_item->SetAttribute("id", item.second->GetID());
		xml_bag->LinkEndChild(xml_item);
	}

	for (const auto& equipment : role.GetBag().GetEquipments())
	{
		if (equipment.second != nullptr)
		{
			TiXmlElement* xml_equipment = new TiXmlElement("Equipment");
			xml_equipment->SetAttribute("id", equipment.second->GetID());
			xml_bag->LinkEndChild(xml_equipment);
		}
	}

	xml_role->LinkEndChild(xml_bag);
	xml_root->LinkEndChild(xml_role);
	xml_doc.LinkEndChild(xml_root);

	xml_doc.SaveFile(CSolution::SAVE_XML_PATH.c_str());
}

void CSolution::LoadXml(CRole& role)
{
	TiXmlDocument xml_doc;
	if (!xml_doc.LoadFile(CSolution::SAVE_XML_PATH.c_str()))
	{
		std::cerr << "读取XML文件失败：" << CSolution::SAVE_XML_PATH << std::endl;
		return;
	}

	TiXmlElement* xml_root = xml_doc.RootElement();

	TiXmlElement* xml_role = xml_root->FirstChildElement("Role");
	if (!xml_role)
	{
		std::cerr << "未找到Role元素：" << CSolution::SAVE_XML_PATH << std::endl;
		return;
	}

	int hp, max_hp, mp, max_mp, atk, def;
	const char* name;

	xml_role->QueryIntAttribute("hp", &hp);
	xml_role->QueryIntAttribute("max_hp", &max_hp);
	xml_role->QueryIntAttribute("mp", &mp);
	xml_role->QueryIntAttribute("max_mp", &max_mp);
	xml_role->QueryIntAttribute("atk", &atk);
	xml_role->QueryIntAttribute("def", &def);
	name = xml_role->Attribute("name");

	role.SetHP(hp);
	role.SetMaxHP(max_hp);
	role.SetMP(mp);
	role.SetMaxMP(max_mp);
	role.SetATK(atk);
	role.SetDEF(def);
	role.SetName(name);

	TiXmlElement* xml_bag = xml_role->FirstChildElement("Bag");
	if (xml_bag)
	{
		CBag bag;

		int item_array_size, item_chosen_index, equipment_chosen_index;
		xml_bag->QueryIntAttribute("item_array_size", &item_array_size);
		xml_bag->QueryIntAttribute("item_chosen_index", &item_chosen_index);
		xml_bag->QueryIntAttribute("equipment_chosen_index", &equipment_chosen_index);

		bag.SetItemArraySize(item_array_size);
		bag.SetItemChosenIndex(item_chosen_index);
		bag.SetEquipmentChosenIndex(equipment_chosen_index);

		for (TiXmlElement* xml_item = xml_bag->FirstChildElement("Item"); xml_item; xml_item = xml_item->NextSiblingElement("Item"))
		{
			int id;
			xml_item->QueryIntAttribute("id", &id);
			bag.AddItem(CItemFC::GetInstance()->CreateItem(id));
		}

		for (TiXmlElement* xml_equipment = xml_bag->FirstChildElement("Equipment"); xml_equipment; xml_equipment = xml_equipment->NextSiblingElement("Equipment"))
		{
			int id;
			xml_equipment->QueryIntAttribute("id", &id);
			bag.Equip(static_cast<CEquipment*>(CItemFC::GetInstance()->CreateItem(id)), &role);
		}

		role.SetBag(bag);
	}
}

void CSolution::Run()
{
	Init();

	initgraph(900, 800);

	CRole role;
	LoadXml(role);

	int item_x = role.GetBag().GetItemChosenIndex() % CBag::ITEM_ARRAY_WIDTH;
	int item_y = role.GetBag().GetItemChosenIndex() / CBag::ITEM_ARRAY_WIDTH;
	int equipment_y = role.GetBag().GetEquipmentChosenIndex() % CEquipment::EEquipmentType::ET_COUNT;

	bool is_running = true;

	while (is_running)
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
			/* ESC键 */
			case 27:
				is_running = false;
				break;
			}
		}
		EndBatchDraw();
	}

	closegraph();

	SaveXml(role);
}
