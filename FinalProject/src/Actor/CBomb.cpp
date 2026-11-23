#include "CBomb.h"

CBomb::CBomb() {}

CBomb::CBomb(const CVector3D& center, const CVector3D& position, const CVector3D& rotation, const CVector3D& scale, int tile_size, CActor::EDirection direction, float velocity, const EBulletFrom& bullet_from, const EBombType& bomb_type, float acceleration)
	: CBullet(center, position, rotation, scale, tile_size, direction, velocity, bullet_from), m_bomb_type(bomb_type), m_acceleration(acceleration) {}

CBomb::~CBomb() {}

void CBomb::Move(const CVector3D& offset)
{
	CBullet::Move(offset);
}

void CBomb::Destroy()
{
	CBullet::Destroy();
}

void CBomb::Draw()
{

}

GET_SET_FUN_DEFINE(CBomb::EBombType, CBomb, m_bomb_type, BombType)
GET_SET_FUN_DEFINE(float, CBomb, m_acceleration, Acceleration)
