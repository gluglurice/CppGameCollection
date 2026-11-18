#include "CItem.h"

#include "src/Game/CGame.h"

int CItem::ITEM_IMG_NUM = 1;
std::wstring CItem::ITEM_IMG_PATHS[] = { L"" };
IMAGE CItem::ITEM_IMAGES[] = { NULL };

float CItem::DEFAULT_VELOCITY = 0.2f;

void CItem::Init()
{

}

CItem::CItem() {}

CItem::CItem(const CActor::Position& position, const EItemType& item_type) : CActor(position), m_item_type(item_type)
{
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
