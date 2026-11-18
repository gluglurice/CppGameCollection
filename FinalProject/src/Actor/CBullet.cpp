#include "CBullet.h"

#include "src/Game/CGame.h"

CActor::EDirection CBullet::DEFAULT_PLAYER_DIRECTION = CActor::EDirection::D_UP;
CActor::EDirection CBullet::DEFAULT_ENEMY_DIRECTION = CActor::EDirection::D_DOWN;

void CBullet::Init()
{

}

CBullet::CBullet() {}

CBullet::CBullet(const CActor::Position& position, const EBulletFrom& bullet_from) : CActor(position), m_bullet_from(bullet_from)
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
}

CBullet::~CBullet() {}

void CBullet::Move(int move_x, int move_y)
{

}

void CBullet::Draw()
{

}

GET_SET_FUN_DEFINE(CBullet::EBulletFrom, CBullet, m_bullet_from, BulletFrom)
