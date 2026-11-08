#include "CLancer.h"

CLancer::CLancer()
{

}

CLancer::CLancer(const Position& position, const std::wstring& img_path)
{
	m_position = position;
	LoadImg(img_path);
}

CLancer::~CLancer()
{

}

void CLancer::Attack(CSoldier& other)
{

}

void CLancer::GotAttackedBy(CSoldier& other)
{

}
