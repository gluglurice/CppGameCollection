#include "CItem.h"

CItem::CItem() {}

CItem::CItem(int id, const std::string& name, EItemType item_type, int hp, int mp, int atk, int def)
	: m_id(id), m_name(name), m_item_type(item_type), m_hp(hp), m_mp(mp), m_atk(atk), m_def(def) {}

CItem::~CItem() {}

GET_SET_FUN_DEFINE(CItem::EItemType, CItem, m_item_type, ItemType)
GET_SET_FUN_DEFINE(int, CItem, m_id, ID)
GET_SET_FUN_DEFINE(int, CItem, m_hp, HP)
GET_SET_FUN_DEFINE(int, CItem, m_mp, MP)
GET_SET_FUN_DEFINE(int, CItem, m_atk, ATK)
GET_SET_FUN_DEFINE(int, CItem, m_def, DEF)
GET_SET_FUN_DEFINE(std::string, CItem, m_name, Name)
