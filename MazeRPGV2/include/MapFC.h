#pragma once

#include <Singleton.h>

#include "Map.h"

class CMapFC : public CSingleton<CMapFC>
{
	friend CSingleton<CMapFC>;

protected:
	map<CMap::MapElem, Image> m_elem_imgs_map;

	map<int, CMap*> m_level_map_map;

	CMapFC();

public:
	~CMapFC();

	Image GetElemImg(CMap::MapElem elem);

	CMap* CreateLevelMap(int level);
};
