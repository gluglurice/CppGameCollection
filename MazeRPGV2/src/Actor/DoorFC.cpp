#include "DoorFC.h"

#include "Game.h"

CDoorFC::CDoorFC()
{
	TiXmlDocument xml_doc;

	if (!xml_doc.LoadFile(CGame::GAME_INI_PATH.c_str()))
	{
		cerr << "打开XML文件失败：" << CGame::GAME_INI_PATH << endl;
		return;
	}

	TiXmlElement* xml_root = xml_doc.RootElement();

	TiXmlElement* xml_doors = xml_root->FirstChildElement("doors");
	for (TiXmlElement* xml_door = xml_doors->FirstChildElement("door"); xml_door; xml_door = xml_door->NextSiblingElement("door"))
	{
		float scale;
		int tile_size;
		CDoor::Type type;
		bool is_open = false;

		xml_door->QueryFloatAttribute("scale", &scale);
		xml_door->QueryIntAttribute("tile_size", &tile_size);
		xml_door->QueryIntAttribute("type", reinterpret_cast<int*>(&type));

		float velocity = 0.0f;
		CVector3D center(tile_size / 2.0f, tile_size / 2.0f, 0);
		CVector3D position_logic(0.0f, 0.0f, 0.0f);
		CVector3D position_render(0.0f, 0.0f, 0.0f);
		CVector3D rotation(0.0f, 0.0f, 0.0f);
		CVector3D scale_vec(scale, scale, 1.0f);

		CActor::SpritesMap sprites;
		map<wstring, Image*> img_map;

		for (TiXmlElement* xml_sprite = xml_door->FirstChildElement("sprite"); xml_sprite; xml_sprite = xml_sprite->NextSiblingElement("sprite"))
		{
			CActor::State sprite_state;
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
			int sprite_index = static_cast<int>(sprite_state);
			sprites[sprite_index] = new CSprite(img, row_num, col_num, center, position_render, rotation, scale_vec, direction, read_mode, play_row, play_col, frame_terminal, cycle_terminal);
		}
		int door_index = static_cast<int>(type);
		m_door_map[door_index] = new CDoor(center, position_logic, position_render, rotation, scale_vec, tile_size, CActor::D_DOWN, velocity, CActor::S_STILL, sprites, type, is_open);
	}
}

CDoorFC::~CDoorFC()
{
	for (auto& pair : m_door_map)
	{
		if (pair.second)
		{
			pair.second->Destroy();
		}
	}
	m_door_map.clear();
}

CDoor* CDoorFC::CreateDoor(CVector3D position_logic, CDoor::Type type, bool is_open)
{
	int door_index = static_cast<int>(type);
	CDoor* door = m_door_map[door_index];
	CActor::SpritesMap new_sprites;

	for (auto& pair : door->GetSprites())
	{
		new_sprites[pair.first] = new CSprite(pair.second->GetImg(), pair.second->GetRowNum(), pair.second->GetColNum(), pair.second->GetCenter(), pair.second->GetPosition(), pair.second->GetRotation(), pair.second->GetScale(), pair.second->GetDirection(), pair.second->GetReadMode(), pair.second->GetPlayRow(), pair.second->GetPlayCol(), pair.second->GetFrameTerminal(), pair.second->GetCycleTerminal());
	}

	CVector3D position_render = position_logic * CGame::MAP_TILE_SIZE + CVector3D(CGame::MAP_TILE_SIZE / 2.0f, CGame::MAP_TILE_SIZE / 2.0f, 0.0f);
	return new CDoor(door->GetCenter(), position_logic, position_render, door->GetRotation(), door->GetScale(), door->GetTileSize(), door->GetDirection(), door->GetVelocity(), door->GetState(), new_sprites, type, is_open);
}
