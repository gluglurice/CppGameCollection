#include "CItem.h"

CItem::CItem() {}

CItem::CItem(const CVector3D& center, const CVector3D& position, const CVector3D& rotation, const CVector3D& scale, int tile_size, CActor::EDirection direction, float velocity, const EItemType& item_type)
	: CActor(center, position, rotation, scale, tile_size, direction, velocity), m_item_type(item_type) {}

CItem::~CItem() {}

void CItem::Move(const CVector3D& offset)
{
	CActor::Move(offset);
}

void CItem::Destroy()
{
	CActor::Destroy();
}

void CItem::Draw()
{

}

GET_SET_FUN_DEFINE(CItem::EItemType, CItem, m_item_type, ItemType)
