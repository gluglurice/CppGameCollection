#include "CBullet.h"

CBullet::CBullet() {}

CBullet::CBullet(const CVector3D& center, const CVector3D& position, const CVector3D& rotation, const CVector3D& scale, int tile_size, CActor::EDirection direction, float velocity, EBulletFrom bullet_from)
	: CActor(center, position, rotation, scale, tile_size, direction, velocity), m_bullet_from(bullet_from) {}

CBullet::~CBullet() {}

void CBullet::Move(const CVector3D& offset)
{
	CActor::Move(offset);
}

void CBullet::Destroy()
{
	CActor::Destroy();
}

void CBullet::Draw()
{

}

GET_SET_FUN_DEFINE(CBullet::EBulletFrom, CBullet, m_bullet_from, BulletFrom)
