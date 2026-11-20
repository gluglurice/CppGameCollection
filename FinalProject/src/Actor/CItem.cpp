#include "CItem.h"

CItem::CItem() {}

CItem::CItem(const CVector3D& position, int tile_size, float scale, CActor::EDirection direction, float velocity, const EItemType& item_type)
	: CActor(position, tile_size, scale, direction, velocity), m_item_type(item_type) {}

CItem::~CItem() {}

void CItem::Move(const CVector3D& offset)
{
	CActor::Move(offset);
}

void CItem::Draw()
{

}

GET_SET_FUN_DEFINE(CItem::EItemType, CItem, m_item_type, ItemType)
