#include "CNormalBulletFC.h"

#include <iostream>

#include <graphics.h>
#include <tinyxml/tinyxml.h>
#include <Utils/Utils.h>

#include "src/Game/CGame.h"

CNormalBulletFC* CNormalBulletFC::m_instance;

CNormalBulletFC* CNormalBulletFC::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new CNormalBulletFC();
	}
	return m_instance;
}

CNormalBulletFC::CNormalBulletFC()
{
	TiXmlDocument xml_doc;
	if (!xml_doc.LoadFile(CGame::GAME_INI_PATH.c_str()))
	{
		std::cerr << "Failed to load game ini file: " << CGame::GAME_INI_PATH << std::endl;
		return;
	}

	TiXmlElement* xml_root = xml_doc.RootElement();
	TiXmlElement* xml_inventory = xml_root->FirstChildElement("Inventory");
	TiXmlElement* xml_normal_bullets = xml_inventory->FirstChildElement("NormalBullets");
	for (TiXmlElement* xml_normal_bullet = xml_normal_bullets->FirstChildElement("NormalBullet"); xml_normal_bullet; xml_normal_bullet = xml_normal_bullet->NextSiblingElement("NormalBullet"))
	{
		int tile_size, type;
		float scale, velocity;
		CNormalBullet* normal_bullet;
		IMAGE* img;

		xml_normal_bullet->QueryIntAttribute("tile_size", &tile_size);
		xml_normal_bullet->QueryFloatAttribute("scale", &scale);
		xml_normal_bullet->QueryFloatAttribute("velocity", &velocity);
		xml_normal_bullet->QueryIntAttribute("type", &type);
		std::wstring img_path = StringToWString(xml_normal_bullet->Attribute("img_path"), "UTF-8");
		img = new IMAGE();

		normal_bullet = new CNormalBullet(CVector3D(0, 0, 0), tile_size, scale, (CActor::EDirection)0, velocity, (CBullet::EBulletFrom)0, (CNormalBullet::ENormalBulletType)type);
		loadimage(img, img_path.c_str());
		m_normal_bullet_map[(CNormalBullet::ENormalBulletType)type] = std::make_pair(normal_bullet, img);
	}
}

CNormalBulletFC::~CNormalBulletFC()
{
	for (auto& pair : m_normal_bullet_map)
	{
		delete pair.second.first;
		delete pair.second.second;
	}
	m_normal_bullet_map.clear();
}

IMAGE* CNormalBulletFC::GetImg(CNormalBullet::ENormalBulletType normal_bullet_type)
{
	return m_normal_bullet_map[normal_bullet_type].second;
}

CNormalBullet* CNormalBulletFC::CreateNormalBullet(const CVector3D& position, CBullet::EBulletFrom bullet_from, CNormalBullet::ENormalBulletType normal_bullet_type)
{
	CNormalBullet* normal_bullet = m_normal_bullet_map[normal_bullet_type].first;
	CActor::EDirection direction = (bullet_from == CBullet::EBulletFrom::BF_PLAYER) ? CActor::EDirection::D_UP : CActor::EDirection::D_DOWN;
	return new CNormalBullet(position, normal_bullet->GetTileSize(), normal_bullet->GetScale(), direction, normal_bullet->GetVelocity(), bullet_from, normal_bullet_type);
}
