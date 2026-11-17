#pragma once

#include <string>

#include <Utils/Utils.h>

class CItem
{
public:
	enum EItemType
	{
		IT_DRUG,
		IT_EQUIPMENT,
	};

GET_SET_FUN_DECLAR(EItemType, m_item_type, ItemType)
GET_SET_FUN_DECLAR(int, m_id, ID)
GET_SET_FUN_DECLAR(int, m_hp, HP)
GET_SET_FUN_DECLAR(int, m_mp, MP)
GET_SET_FUN_DECLAR(int, m_atk, ATK)
GET_SET_FUN_DECLAR(int, m_def, DEF)
GET_SET_FUN_DECLAR(std::string, m_name, Name)

public:
	CItem();

	CItem(int id, const std::string& name, EItemType item_type, int hp, int mp, int atk, int def);

	~CItem();
};
