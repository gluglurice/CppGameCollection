#include "CBomb.h"

int CBomb::IMG_NUM;
std::wstring* CBomb::IMG_PATHS;
IMAGE* CBomb::IMGS;

float CBomb::DEFAULT_VELOCITY;
float CBomb::DEFAULT_ACCELERATION;

void CBomb::Init(const std::string& config_path)
{
	CBomb::IMG_NUM = 1;
	CBomb::IMG_PATHS = new std::wstring[CBomb::IMG_NUM];
	CBomb::IMGS = new IMAGE[CBomb::IMG_NUM];

	CBomb::DEFAULT_VELOCITY = 3.0f;
	CBomb::DEFAULT_ACCELERATION = 0.5;
}

void CBomb::Delete()
{
	if (CBomb::IMG_PATHS)
	{
		delete[] CBomb::IMG_PATHS;
		CBomb::IMG_PATHS = nullptr;
	}
	if (CBomb::IMGS)
	{
		delete[] CBomb::IMGS;
		CBomb::IMGS = nullptr;
	}
}

CBomb::CBomb() {}

CBomb::CBomb(const CActor::Position& position, const EBulletFrom& bullet_from, const EBombType& bomb_type)
	: CBullet(position, bullet_from), m_bomb_type(bomb_type)
{
	m_velocity = CBomb::DEFAULT_VELOCITY;
	m_acceleration = CBomb::DEFAULT_ACCELERATION;
}

CBomb::~CBomb() {}

void CBomb::Move(int move_x, int move_y)
{

}

void CBomb::Draw()
{

}

GET_SET_FUN_DEFINE(CBomb::EBombType, CBomb, m_bomb_type, BombType)
GET_SET_FUN_DEFINE(float, CBomb, m_acceleration, Acceleration)
