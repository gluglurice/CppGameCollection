#include "CArcher.h"

CArcher::CArcher()
{

}

CArcher::CArcher(const Position& position, const std::wstring& img_path)
{
	m_position = position;
	LoadImg(img_path);
}

CArcher::~CArcher()
{

}

void CArcher::Attack(CSoldier& other)
{

}

void CArcher::GotAttackedBy(CSoldier& other)
{

}
