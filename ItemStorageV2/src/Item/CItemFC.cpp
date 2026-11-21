#include "CItemFC.h"

#include <iostream>
#include <string>

#include <tinyxml.h>

#include "src/Solution/CSolution.h"
#include "CItem.h"
#include "CDrug.h"
#include "CEquipment.h"

CItemFC* CItemFC::m_instance;

CItemFC* CItemFC::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CItemFC();
	}
	return m_instance;
}

CItemFC::CItemFC()
{
	CItemFC::Init();
}

void CItemFC::Init()
{
	TiXmlDocument xml_doc;

	if (!xml_doc.LoadFile(CSolution::INI_XML_PATH.c_str()))
	{
		std::cerr << "读取XML文件失败：" << CSolution::INI_XML_PATH << std::endl;
		return;
	}

	TiXmlElement* xml_root = xml_doc.RootElement();
	TiXmlElement* xml_items = xml_root->FirstChildElement("Items");

	for (TiXmlElement* xml_item = xml_items->FirstChildElement("Item"); xml_item; xml_item = xml_item->NextSiblingElement("Item"))
	{
		CItem* item;

		int item_type, equipment_type, drug_type;
		int id, item_hp, item_mp, item_atk, item_def;
		std::string item_name;

		std::wstring item_img_path;
		IMAGE item_img;

		xml_item->QueryIntAttribute("item_type", &item_type);
		xml_item->QueryIntAttribute("id", &id);
		xml_item->QueryIntAttribute("hp", &item_hp);
		xml_item->QueryIntAttribute("mp", &item_mp);
		xml_item->QueryIntAttribute("atk", &item_atk);
		xml_item->QueryIntAttribute("def", &item_def);
		item_name = xml_item->Attribute("name");
		item_img_path = StringToWString(xml_item->Attribute("img_path"), CSolution::XML_ENCODING.c_str());
		switch (static_cast<CItem::EItemType>(item_type))
		{
		case CItem::EItemType::IT_DRUG:
			xml_item->QueryIntAttribute("drug_type", &drug_type);
			item = new CDrug(id, item_name, CItem::EItemType::IT_DRUG, static_cast<CDrug::EDrugType>(drug_type), item_hp, item_mp, item_atk, item_def);
			break;
		case CItem::EItemType::IT_EQUIPMENT:
			xml_item->QueryIntAttribute("equipment_type", &equipment_type);
			item = new CEquipment(id, item_name, CItem::EItemType::IT_EQUIPMENT, static_cast<CEquipment::EEquipmentType>(equipment_type), item_hp, item_mp, item_atk, item_def);
			break;
		default:
			item = new CItem();
			break;
		}
		loadimage(&item_img, item_img_path.c_str());

		m_item_map[id] = std::make_pair(item, item_img);
	}
}

CItemFC::~CItemFC()
{
	for (auto& item_pair : m_item_map)
	{
		delete item_pair.second.first;
	}
	m_item_map.clear();
}

CItem* CItemFC::CreateItem(int id)
{
	auto it = m_item_map.find(id);
	if (it != m_item_map.end())
	{
		CItem* item = it->second.first;
		switch (item->GetItemType())
		{
		case CItem::EItemType::IT_DRUG:
			return new CDrug(*static_cast<CDrug*>(item));
		case CItem::EItemType::IT_EQUIPMENT:
			return new CEquipment(*static_cast<CEquipment*>(item));
		default:
			return new CItem(*item);
		}
	}
	return new CItem();
}

std::map<int, std::pair<CItem*, IMAGE>>& CItemFC::GetItemMap()
{
	return m_item_map;
}
