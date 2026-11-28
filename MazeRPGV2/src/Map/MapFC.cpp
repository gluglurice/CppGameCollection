#include "MapFC.h"

#include <fstream>

#include "Game.h"
#include "Door.h"
#include "DoorFC.h"

CMapFC::CMapFC()
{
	TiXmlDocument xml_doc;

	if (!xml_doc.LoadFile(CGame::GAME_INI_PATH.c_str()))
	{
		cerr << "打开XML文件失败：" << CGame::GAME_INI_PATH << endl;
		return;
	}

	TiXmlElement* xml_root = xml_doc.RootElement();
	TiXmlElement* xml_maps = xml_root->FirstChildElement("maps");

	int tile_size;
	float scale;
	xml_maps->QueryIntAttribute("tile_size", &tile_size);
	xml_maps->QueryFloatAttribute("scale", &scale);

	for (TiXmlElement* xml_elem = xml_maps->FirstChildElement("elems")->FirstChildElement("elem"); xml_elem; xml_elem = xml_elem->NextSiblingElement("elem"))
	{
		int elem_type;
		Image elem_img;

		xml_elem->QueryIntAttribute("type", &elem_type);
		string elem_img_path = xml_elem->Attribute("img_path");
		wstring elem_img_path_w(elem_img_path.begin(), elem_img_path.end());

		CGraphic::GetInstance()->LoadTex(elem_img_path_w.c_str(), elem_img);
		m_elem_imgs_map[static_cast<CMap::MapElem>(elem_type)] = elem_img;
	}

	int level = 0;
	for (TiXmlElement* xml_map = xml_maps->FirstChildElement("map"); xml_map; xml_map = xml_map->NextSiblingElement("map"))
	{
		CMap* map;

		int row;
		int col;
		CVector3D start_position_logic(0.0f, 0.0f, 0.0f);
		string src_txt_path = xml_map->Attribute("src_txt_path");

		/* 根据 txt 读取地图地形数据 */
		ifstream in_file(src_txt_path, ios::in);
		if (!in_file)
		{
			cerr << "打开地图文件失败：" << src_txt_path << endl;
			return;
		}
		in_file >> col >> row >> start_position_logic.x >> start_position_logic.y;

		vector<vector<vector<CMap::MapElem>>> map_vals(
			static_cast<int>(CMap::Layer::L_COUNT),vector<vector<CMap::MapElem>>(
				row, vector<CMap::MapElem>(
					col, CMap::ME_EMPTY)));

		CMap::ObjectsMap objects;
		CVector3D object_position_logic(0.0f, 0.0f, 0.0f);

		for (int layer = 0; layer < static_cast<int>(CMap::Layer::L_COUNT); layer++)
		{
			for (int r = 0; r < row; r++)
			{
				for (int c = 0; c < col; c++)
				{
					int elem_val;
					in_file >> elem_val;
					map_vals[layer][r][c] = static_cast<CMap::MapElem>(elem_val);

					switch (elem_val)
					{
					case CMap::ME_DOOR_SINGLE_OPEN:
						object_position_logic = CVector3D(static_cast<float>(c), static_cast<float>(r), 0.0f);
						objects[object_position_logic] = CDoorFC::GetInstance()->CreateDoor(object_position_logic, CDoor::T_SINGLE, true);
						break;
					case CMap::ME_DOOR_SINGLE_CLOSED:
						object_position_logic = CVector3D(static_cast<float>(c), static_cast<float>(r), 0.0f);
						objects[object_position_logic] = CDoorFC::GetInstance()->CreateDoor(object_position_logic, CDoor::T_SINGLE, false);
						break;
					case CMap::ME_DOOR_DOUBLE_LEFT_OPEN:
						object_position_logic = CVector3D(static_cast<float>(c), static_cast<float>(r), 0.0f);
						objects[object_position_logic] = CDoorFC::GetInstance()->CreateDoor(object_position_logic, CDoor::T_DOUBLE_LEFT, true);
						break;
					case CMap::ME_DOOR_DOUBLE_LEFT_CLOSED:
						object_position_logic = CVector3D(static_cast<float>(c), static_cast<float>(r), 0.0f);
						objects[object_position_logic] = CDoorFC::GetInstance()->CreateDoor(object_position_logic, CDoor::T_DOUBLE_LEFT, false);
						break;
					case CMap::ME_DOOR_DOUBLE_RIGHT_OPEN:
						object_position_logic = CVector3D(static_cast<float>(c), static_cast<float>(r), 0.0f);
						objects[object_position_logic] = CDoorFC::GetInstance()->CreateDoor(object_position_logic, CDoor::T_DOUBLE_RIGHT, true);
						break;
					case CMap::ME_DOOR_DOUBLE_RIGHT_CLOSED:
						object_position_logic = CVector3D(static_cast<float>(c), static_cast<float>(r), 0.0f);
						objects[object_position_logic] = CDoorFC::GetInstance()->CreateDoor(object_position_logic, CDoor::T_DOUBLE_RIGHT, false);
						break;
					}
				}
			}
		}

		map = new CMap(level, col, row, tile_size, scale, map_vals, start_position_logic, objects);

		m_level_maps_origin.push_back(map);
		m_level_maps.push_back(map);
		level++;
	}
}

CMapFC::~CMapFC()
{
	m_elem_imgs_map.clear();

	for (auto& map : m_level_maps_origin)
	{
		delete map;
	}
	m_level_maps_origin.clear();

	for (auto& map : m_level_maps)
	{
		delete map;
	}
	m_level_maps.clear();
}

Image CMapFC::GetElemImg(CMap::MapElem elem)
{
	return m_elem_imgs_map[elem];
}

CMap* CMapFC::GetLevelMap(int level)
{
	return m_level_maps[level];
}

int CMapFC::GetLevelCount()
{
	return static_cast<int>(m_level_maps.size());
}
