#include "CBullet.h"

CBullet::CBullet() {}

CBullet::CBullet(const CActor::Position& position, const EBulletFrom& bullet_from, const EBulletType& bullet_type) : CActor(position), m_bullet_from(bullet_from), m_bullet_type(bullet_type)
{
	switch (m_bullet_from)
	{
	case CBullet::EBulletFrom::BF_PLAYER:
		m_direction = CBullet::DEFAULT_PLAYER_DIRECTION;
		break;
	case CBullet::EBulletFrom::BF_ENEMY:
		m_direction = CBullet::DEFAULT_ENEMY_DIRECTION;
		break;
	}

	m_velocity = CBullet::DEFAULT_VELOCITY;
}

CBullet::~CBullet() {}

void CBullet::Move(int move_x, int move_y)
{

}

void CBullet::Draw()
{

}

GET_SET_FUN_DEFINE(CBullet::EBulletFrom, CBullet, m_bullet_from, BulletFrom)
GET_SET_FUN_DEFINE(CBullet::EBulletType, CBullet, m_bullet_type, BulletType)
