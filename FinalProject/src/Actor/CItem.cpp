#include "CItem.h"

CItem::CItem() {}

CItem::CItem(const CActor::Position& position, const EItemType& item_type) : CActor(position), m_item_type(item_type)
{
	m_direction = CItem::DEFAULT_DIRECTION;
	m_velocity = CItem::DEFAULT_VELOCITY;
}

CItem::~CItem() {}

void CItem::Move(int move_x, int move_y)
{

}

void CItem::Draw()
{

}

GET_SET_FUN_DEFINE(CItem::EItemType, CItem, m_item_type, ItemType)
