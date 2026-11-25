#include "CharacterFC.h"

#include "Game.h"

CCharacterFC::CCharacterFC()
{
	TiXmlDocument xml_doc;

	if (!xml_doc.LoadFile(CGame::GAME_INI_PATH.c_str()))
	{
		cerr << "打开XML文件失败：" << CGame::GAME_INI_PATH << endl;
		return;
	}

	TiXmlElement* xml_root = xml_doc.RootElement();
	TiXmlElement* xml_characters = xml_root->FirstChildElement("characters");

	for (TiXmlElement* xml_character = xml_characters->FirstChildElement("character"); xml_character; xml_character = xml_character->NextSiblingElement("character"))
	{
		float scale;
		int tile_size;
		float velocity;
		CCharacter::Type character_type;
		xml_character->QueryFloatAttribute("scale", &scale);
		xml_character->QueryIntAttribute("tile_size", &tile_size);
		xml_character->QueryFloatAttribute("velocity", &velocity);
		xml_character->QueryIntAttribute("type", reinterpret_cast<int*>(&character_type));

		D3DXVECTOR3 center(tile_size * scale / 2.0f, tile_size * scale / 2.0f, 0);
		D3DXVECTOR3 position(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 rotation(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 scale_vec(scale, scale, 1.0f);

		map<CCharacter::State, CSprite*> sprite_map;

		for (TiXmlElement* xml_sprite = xml_character->FirstChildElement("sprite"); xml_sprite; xml_sprite = xml_sprite->NextSiblingElement("sprite"))
		{
			CCharacter::State sprite_state;
			int row_num;
			int col_num;
			float scale;
			CSprite::Direction default_direction;
			unsigned frame_terminal;
			unsigned cycle_terminal;
			wstring img_path;

			xml_sprite->QueryIntAttribute("state", reinterpret_cast<int*>(&sprite_state));
			xml_sprite->QueryIntAttribute("row_num", &row_num);
			xml_sprite->QueryIntAttribute("col_num", &col_num);
			xml_sprite->QueryFloatAttribute("scale", &scale);
			xml_sprite->QueryIntAttribute("default_direction", reinterpret_cast<int*>(&default_direction));
			xml_sprite->QueryUnsignedAttribute("frame_terminal", &frame_terminal);
			xml_sprite->QueryUnsignedAttribute("cycle_terminal", &cycle_terminal);
			img_path = StringToWString(xml_sprite->Attribute("img_path"), "UTF-8");

			Image* img = new Image();
			CGraphic::GetInstance()->LoadTex(img_path.c_str(), *img);
			sprite_map[sprite_state] = new CSprite(img, row_num, col_num, center, position, rotation, scale_vec, default_direction, CSprite::RM_ONE_ROW, 1, 0, frame_terminal, cycle_terminal);
		}
		CCharacter* character = new CCharacter(center, position, rotation, scale_vec, tile_size, CActor::D_DOWN, velocity, character_type, CCharacter::S_IDLE, sprite_map);
		m_character_map[character_type] = character;
	}
}

CCharacterFC::~CCharacterFC()
{
	for (auto& pair : m_character_map)
	{
		delete pair.second;
	}
	m_character_map.clear();
}

CCharacter* CCharacterFC::CreateCharacter(D3DXVECTOR3 position, CCharacter::Type type)
{
	CCharacter* character = m_character_map[type];
	CCharacter::SpriteMap new_sprite_map;

	for (auto& pair : character->GetSpriteMap())
	{
		CSprite* sprite = pair.second;
		new_sprite_map[pair.first] = new CSprite(sprite->GetImg(), sprite->GetRowNum(), sprite->GetColNum(), sprite->GetCenter(), sprite->GetPosition(), sprite->GetRotation(), sprite->GetScale(), sprite->GetDefaultDirection(), sprite->GetReadMode(), sprite->GetPlayRow(), sprite->GetPlayCol(), sprite->GetFrameTerminal(), sprite->GetCycleTerminal());
	}

	return new CCharacter(character->GetCenter(), position, character->GetRotation(), character->GetScale(), character->GetTileSize(), character->GetDirection(), character->GetVelocity(), type, character->GetState(), new_sprite_map);
}
