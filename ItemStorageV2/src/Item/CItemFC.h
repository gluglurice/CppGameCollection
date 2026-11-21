#pragma once

#include <map>

#include <EasyXExtension.h>

class CItem;

class CItemFC
{
private:
	static CItemFC* m_instance;

public:
	static CItemFC* GetInstance();

private:
	std::map<int, std::pair<CItem*, IMAGE>> m_item_map;

private:
	CItemFC();

	void Init();

public:
	~CItemFC();

	CItem* CreateItem(int id);

	std::map<int, std::pair<CItem*, IMAGE>>& GetItemMap();
};
