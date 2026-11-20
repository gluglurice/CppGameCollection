#include "CBullet.h"

CBullet::CBullet() {}

CBullet::CBullet(const CVector3D& position, int tile_size, float scale, CActor::EDirection direction, float velocity, EBulletFrom bullet_from)
	: CActor(position, tile_size, scale, direction, velocity), m_bullet_from(bullet_from) {}

CBullet::~CBullet() {}

void CBullet::Move(const CVector3D& offset)
{
	CActor::Move(offset);
}

void CBullet::Draw()
{

}

GET_SET_FUN_DEFINE(CBullet::EBulletFrom, CBullet, m_bullet_from, BulletFrom)
