#include "CBomb.h"

#include "src/Game/CGame.h"

int CBomb::BOMB_IMG_NUM = 1;
std::wstring CBomb::BOMB_IMG_PATHS[] = { L"" };
IMAGE CBomb::BOMB_IMAGES[] = { NULL };

float CBomb::DEFAULT_VELOCITY = 3.0f;
float CBomb::DEFAULT_ACCELERATION = 0.5;

void CBomb::Init()
{

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
