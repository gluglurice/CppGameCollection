#include "CNormalBullet.h"

#include "src/Game/CGame.h"

float CNormalBullet::DEFAULT_VELOCITY = 5.0f;

void CNormalBullet::Init()
{

}

CNormalBullet::CNormalBullet() {}

CNormalBullet::CNormalBullet(const CActor::Position& position, const EBulletFrom& bullet_from, const ENormalBulletType& normal_bullet_type)
	: CBullet(position, bullet_from), m_normal_bullet_type(normal_bullet_type)
{
	m_velocity = CNormalBullet::DEFAULT_VELOCITY;
}

CNormalBullet::~CNormalBullet() {}

void CNormalBullet::Move(int move_x, int move_y)
{

}

void CNormalBullet::Draw()
{

}

GET_SET_FUN_DEFINE(CNormalBullet::ENormalBulletType, CNormalBullet, m_normal_bullet_type, NormalBulletType)
