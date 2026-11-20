#include "CShipFC.h"

#include <iostream>

#include <graphics.h>
#include <tinyxml/tinyxml.h>
#include <Utils/Utils.h>

#include "src/Game/CGame.h"

CShipFC* CShipFC::m_instance;

CShipFC* CShipFC::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new CShipFC();
	}
	return m_instance;
}

CShipFC::CShipFC()
{
	TiXmlDocument xml_doc;
	if (!xml_doc.LoadFile(CGame::GAME_INI_PATH.c_str()))
	{
		std::cerr << "读取XML文件失败：" << CGame::GAME_INI_PATH << std::endl;
		return;
	}

	TiXmlElement* xml_root = xml_doc.RootElement();
	TiXmlElement* xml_inventory = xml_root->FirstChildElement("Inventory");
	TiXmlElement* xml_ships = xml_inventory->FirstChildElement("Ships");
	for (TiXmlElement* xml_ship = xml_ships->FirstChildElement("Ship"); xml_ship; xml_ship = xml_ship->NextSiblingElement("Ship"))
	{
		int tile_size, type, max_hp, max_mp, atk, def, shield, normal_bullet_type, bomb_type;
		float scale, velocity, firing_rate;
		CShip* ship;
		IMAGE* img;

		xml_ship->QueryIntAttribute("tile_size", &tile_size);
		xml_ship->QueryFloatAttribute("scale", &scale);
		xml_ship->QueryFloatAttribute("velocity", &velocity);
		xml_ship->QueryIntAttribute("type", &type);
		xml_ship->QueryIntAttribute("max_hp", &max_hp);
		xml_ship->QueryIntAttribute("max_mp", &max_mp);
		xml_ship->QueryIntAttribute("atk", &atk);
		xml_ship->QueryFloatAttribute("firing_rate", &firing_rate);
		xml_ship->QueryIntAttribute("def", &def);
		xml_ship->QueryIntAttribute("shield", &shield);
		xml_ship->QueryIntAttribute("normal_bullet_type", &normal_bullet_type);
		xml_ship->QueryIntAttribute("bomb_type", &bomb_type);
		std::wstring img_path = StringToWString(xml_ship->Attribute("img_path"), "UTF-8");
		img = new IMAGE();

		ship = new CShip(CVector3D(0, 0, 0), tile_size, scale, (CActor::EDirection)0, velocity, (CShip::EShipCamp)0, (CShip::EShipType)type, max_hp, max_hp, max_mp, max_mp, atk, firing_rate, def, shield, (CShip::ENormalBulletType)normal_bullet_type, (CShip::EBombType)bomb_type);
		loadimage(img, img_path.c_str());
		m_ship_map[(CShip::EShipType)type] = std::make_pair(ship, img);
	}
}

CShipFC::~CShipFC()
{
	for (auto& pair : m_ship_map)
	{
		delete pair.second.first;
		delete pair.second.second;
	}
	m_ship_map.clear();
}

IMAGE* CShipFC::GetImg(CShip::EShipType ship_type)
{
	return m_ship_map[ship_type].second;
}

CShip* CShipFC::CreateShip(const CVector3D& position, CShip::EShipCamp ship_camp, CShip::EShipType ship_type)
{
	CShip* ship = m_ship_map[ship_type].first;
	CActor::EDirection direction = (ship_camp == CShip::EShipCamp::SC_PLAYER) ? CActor::EDirection::D_UP : CActor::EDirection::D_DOWN;
	return new CShip(position, ship->GetTileSize(), ship->GetScale(), direction, ship->GetVelocity(), ship_camp, ship_type, ship->GetMaxHP(), ship->GetMaxHP(), ship->GetMaxMP(), ship->GetMaxMP(), ship->GetAtk(), ship->GetFiringRate(), ship->GetDef(), ship->GetShield(), ship->GetNormalBulletType(), ship->GetBombType());
}
