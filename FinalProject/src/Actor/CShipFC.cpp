#include "CShipFC.h"

#include "src/Game/CGame.h"

map<CShip::EShipType, pair<CShip*, Image*>> CShipFC::m_ship_map;

CShipFC::CShipFC()
{
	TiXmlDocument xml_doc;
	if (!xml_doc.LoadFile(CGame::GAME_INI_PATH.c_str()))
	{
		cerr << "读取XML文件失败：" << CGame::GAME_INI_PATH << endl;
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
		Image* img;

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
		wstring img_path = StringToWString(xml_ship->Attribute("img_path"), "UTF-8");
		img = new Image();

		ship = new CShip(CVector3D(0, 0, 0), CVector3D(0, 0, 0), CVector3D(0, 0, 0), CVector3D(scale, scale, scale), tile_size, (CActor::EDirection)0, velocity, (CShip::EShipCamp)0, (CShip::EShipType)type, max_hp, max_hp, max_mp, max_mp, atk, firing_rate, def, shield, (CShip::ENormalBulletType)normal_bullet_type, (CShip::EBombType)bomb_type);
		CGraphic::GetInstance()->LoadTex(img_path.c_str(), *img);
		m_ship_map[(CShip::EShipType)type] = make_pair(ship, img);
	}
}

Image* CShipFC::GetImg(CShip::EShipType ship_type)
{
	return m_ship_map[ship_type].second;
}

CShip* CShipFC::CreateShip(const CVector3D& position, CShip::EShipCamp ship_camp, CShip::EShipType ship_type)
{
	CShip* ship = m_ship_map[ship_type].first;
	CActor::EDirection direction = (ship_camp == CShip::EShipCamp::SC_PLAYER) ? CActor::EDirection::D_UP : CActor::EDirection::D_DOWN;
	return new CShip(ship->GetCenter(), position, ship->GetRotation(), ship->GetScale(), ship->GetTileSize(), direction, ship->GetVelocity(), ship_camp, ship_type, ship->GetMaxHP(), ship->GetMaxHP(), ship->GetMaxMP(), ship->GetMaxMP(), ship->GetAtk(), ship->GetFiringRate(), ship->GetDef(), ship->GetShield(), ship->GetNormalBulletType(), ship->GetBombType());
}
