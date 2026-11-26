#include "MapFC.h"

#include <sstream>

#include "Game.h"

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
		vector<vector<CMap::MapElem>> map_vals;

		int row = 0;
		for (TiXmlElement* xml_row = xml_map->FirstChildElement("row"); xml_row; xml_row = xml_row->NextSiblingElement("row"))
		{
			string cols = xml_row->Attribute("cols");
			istringstream iss(cols);
			vector<CMap::MapElem> row_vals;
			int elem_type;
			while (iss >> elem_type)
			{
				row_vals.push_back(static_cast<CMap::MapElem>(elem_type));
			}
			map_vals.push_back(row_vals);
			row++;
		}

		map = new CMap(level, map_vals[0].size(), map_vals.size(), tile_size, scale, map_vals);

		m_level_map_map[level] = map;
		level++;
	}
}

CMapFC::~CMapFC()
{
	m_elem_imgs_map.clear();
	for (auto& pair : m_level_map_map)
	{
		delete pair.second;
	}
	m_level_map_map.clear();
}

Image CMapFC::GetElemImg(CMap::MapElem elem)
{
	return m_elem_imgs_map[elem];
}

CMap* CMapFC::CreateLevelMap(int level)
{
	return new CMap(*m_level_map_map[level]);
}
