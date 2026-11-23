#include "CNormalBulletFC.h"

#include "src/Game/CGame.h"

map<CNormalBullet::ENormalBulletType, pair<CNormalBullet*, Image*>> CNormalBulletFC::m_normal_bullet_map;

CNormalBulletFC::CNormalBulletFC()
{
	TiXmlDocument xml_doc;
	if (!xml_doc.LoadFile(CGame::GAME_INI_PATH.c_str()))
	{
		cerr << "读取游戏配置文件失败：" << CGame::GAME_INI_PATH << endl;
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
		Image* img;

		xml_normal_bullet->QueryIntAttribute("tile_size", &tile_size);
		xml_normal_bullet->QueryFloatAttribute("scale", &scale);
		xml_normal_bullet->QueryFloatAttribute("velocity", &velocity);
		xml_normal_bullet->QueryIntAttribute("type", &type);
		wstring img_path = StringToWString(xml_normal_bullet->Attribute("img_path"), "UTF-8");
		img = new Image();

		normal_bullet = new CNormalBullet(CVector3D(tile_size / 2.0f, tile_size / 2.0f, 0), CVector3D(0, 0, 0), CVector3D(0, 0, 0), CVector3D(scale, scale, scale), tile_size, (CActor::EDirection)0, velocity, (CBullet::EBulletFrom)0, (CNormalBullet::ENormalBulletType)type);
		CGraphic::GetInstance()->LoadTex(img_path.c_str(), *img);
		m_normal_bullet_map[(CNormalBullet::ENormalBulletType)type] = make_pair(normal_bullet, img);
	}
}

Image* CNormalBulletFC::GetImg(CNormalBullet::ENormalBulletType normal_bullet_type)
{
	return m_normal_bullet_map[normal_bullet_type].second;
}

CNormalBullet* CNormalBulletFC::CreateNormalBullet(const CVector3D& position, CBullet::EBulletFrom bullet_from, CNormalBullet::ENormalBulletType normal_bullet_type)
{
	CNormalBullet* normal_bullet = m_normal_bullet_map[normal_bullet_type].first;
	CActor::EDirection direction = (bullet_from == CBullet::EBulletFrom::BF_PLAYER) ? CActor::EDirection::D_UP : CActor::EDirection::D_DOWN;
	return new CNormalBullet(normal_bullet->GetCenter(), position, normal_bullet->GetRotation(), normal_bullet->GetScale(), normal_bullet->GetTileSize(), direction, normal_bullet->GetVelocity(), bullet_from, normal_bullet_type);
}
