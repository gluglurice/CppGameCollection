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

		CVector3D center(tile_size / 2.0f, tile_size / 2.0f, 0);
		CVector3D position_logic(0.0f, 0.0f, 0.0f);
		CVector3D position_render(0.0f, 0.0f, 0.0f);
		CVector3D rotation(0.0f, 0.0f, 0.0f);
		CVector3D scale_vec(scale, scale, 1.0f);

		vector<CSprite*> sprites = vector<CSprite*>(static_cast<int>(CCharacter::S_COUNT) * static_cast<int>(CActor::D_COUNT));
		map<wstring, Image*> img_map;

		for (TiXmlElement* xml_sprite = xml_character->FirstChildElement("sprite"); xml_sprite; xml_sprite = xml_sprite->NextSiblingElement("sprite"))
		{
			CCharacter::State sprite_state;
			int row_num;
			int col_num;
			CSprite::Direction direction;
			CSprite::ReadMode read_mode;
			int play_row;
			int play_col;
			float frame_terminal;
			float cycle_terminal;

			Image* img;

			xml_sprite->QueryIntAttribute("state", reinterpret_cast<int*>(&sprite_state));
			xml_sprite->QueryIntAttribute("row_num", &row_num);
			xml_sprite->QueryIntAttribute("col_num", &col_num);
			xml_sprite->QueryIntAttribute("direction", reinterpret_cast<int*>(&direction));
			xml_sprite->QueryIntAttribute("read_mode", reinterpret_cast<int*>(&read_mode));
			xml_sprite->QueryIntAttribute("play_row", &play_row);
			xml_sprite->QueryIntAttribute("play_col", &play_col);
			xml_sprite->QueryFloatAttribute("frame_terminal", &frame_terminal);
			xml_sprite->QueryFloatAttribute("cycle_terminal", &cycle_terminal);
			string img_path = xml_sprite->Attribute("img_path");
			wstring img_path_w(img_path.begin(), img_path.end());

			if (img_map.find(img_path_w) != img_map.end())
			{
				img = img_map[img_path_w];
			}
			else
			{
				img = new Image();
				CGraphic::GetInstance()->LoadTex(img_path_w.c_str(), *img);
				img_map[img_path_w] = img;
			}
			int sprite_index = static_cast<int>(sprite_state) * static_cast<int>(CActor::Direction::D_COUNT) + static_cast<int>(direction);
			sprites[sprite_index] = new CSprite(img, row_num, col_num, center, position_render, rotation, scale_vec, direction, read_mode, play_row, play_col, frame_terminal, cycle_terminal);
		}
		CCharacter* character = new CCharacter(center, position_logic, position_render, rotation, scale_vec, tile_size, CActor::D_DOWN, velocity, character_type, CCharacter::S_IDLE, sprites);
		m_character_map[character_type] = character;
	}
}

CCharacterFC::~CCharacterFC()
{
	for (auto& pair : m_character_map)
	{
		if (pair.second)
		{
			pair.second->Destroy();
		}
	}
	m_character_map.clear();
}

CCharacter* CCharacterFC::CreateCharacter(CVector3D position_logic, CCharacter::Type type)
{
	CCharacter* character = m_character_map[type];
	vector<CSprite*> new_sprites;

	for (auto& sprite : character->GetSprites())
	{
		new_sprites.push_back(new CSprite(sprite->GetImg(), sprite->GetRowNum(), sprite->GetColNum(), sprite->GetCenter(), sprite->GetPosition(), sprite->GetRotation(), sprite->GetScale(), sprite->GetDirection(), sprite->GetReadMode(), sprite->GetPlayRow(), sprite->GetPlayCol(), sprite->GetFrameTerminal(), sprite->GetCycleTerminal()));
	}

	return new CCharacter(character->GetCenter(), position_logic, position_logic * CGame::MAP_TILE_SIZE + CVector3D(CGame::MAP_TILE_SIZE / 2.0f, CGame::MAP_TILE_SIZE / 2.0f, 0.0f), character->GetRotation(), character->GetScale(), character->GetTileSize(), character->GetDirection(), character->GetVelocity(), type, character->GetState(), new_sprites);
}
