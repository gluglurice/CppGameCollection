#pragma once

#include <Singleton.h>

#include "Map.h"

class CMapFC : public CSingleton<CMapFC>
{
	friend CSingleton<CMapFC>;

protected:
	map<CMap::MapElem, Image> m_elem_imgs_map;

	vector<CMap*> m_level_maps_origin;

	vector<CMap*> m_level_maps;

	CMapFC();

public:
	~CMapFC();

	Image GetElemImg(CMap::MapElem elem);

	CMap* CreateLevelMap(int level);
};
