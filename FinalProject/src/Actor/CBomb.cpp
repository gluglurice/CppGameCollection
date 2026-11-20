#include "CBomb.h"

CBomb::CBomb() {}

CBomb::CBomb(const CVector3D& position, int tile_size, float scale, CActor::EDirection direction, float velocity, const EBulletFrom& bullet_from, const EBombType& bomb_type, float acceleration)
	: CBullet(position, tile_size, scale, direction, velocity, bullet_from), m_bomb_type(bomb_type), m_acceleration(acceleration) {}

CBomb::~CBomb() {}

void CBomb::Move(const CVector3D& offset)
{
	CBullet::Move(offset);
}

void CBomb::Draw()
{

}

GET_SET_FUN_DEFINE(CBomb::EBombType, CBomb, m_bomb_type, BombType)
GET_SET_FUN_DEFINE(float, CBomb, m_acceleration, Acceleration)
