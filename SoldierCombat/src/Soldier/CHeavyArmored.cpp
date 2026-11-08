#include "CHeavyArmored.h"

CHeavyArmored::CHeavyArmored()
{

}

CHeavyArmored::CHeavyArmored(const Position& position, const std::wstring& img_path)
{
	m_position = position;
	LoadImg(img_path);
}

CHeavyArmored::~CHeavyArmored()
{

}

void CHeavyArmored::Attack(CSoldier& other)
{

}

void CHeavyArmored::GotAttackedBy(CSoldier& other)
{

}
