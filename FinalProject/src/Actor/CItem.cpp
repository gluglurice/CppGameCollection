#include "CItem.h"

int CItem::IMG_NUM;
std::wstring* CItem::IMG_PATHS;
IMAGE* CItem::IMGS;

float CItem::DEFAULT_VELOCITY;

void CItem::Init(const std::string& config_path)
{
	CItem::IMG_NUM = 1;
	CItem::IMG_PATHS = new std::wstring[CItem::IMG_NUM];
	CItem::IMGS = new IMAGE[CItem::IMG_NUM];

	CItem::DEFAULT_VELOCITY = 0.2f;
}

void CItem::Delete()
{
	if (CItem::IMG_PATHS)
	{
		delete[] CItem::IMG_PATHS;
		CItem::IMG_PATHS = nullptr;
	}
	if (CItem::IMGS)
	{
		delete[] CItem::IMGS;
		CItem::IMGS = nullptr;
	}
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
