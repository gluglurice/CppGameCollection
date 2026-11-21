#include "CNormalBullet.h"

#include "CNormalBulletFC.h"

CNormalBullet::CNormalBullet() {}

CNormalBullet::CNormalBullet(const CVector3D& position, int tile_size, float scale, CActor::EDirection direction, float velocity, EBulletFrom bullet_from, ENormalBulletType normal_bullet_type)
	: CBullet(position, tile_size, scale, direction, velocity, bullet_from), m_normal_bullet_type(normal_bullet_type) {}

CNormalBullet::~CNormalBullet() {}

void CNormalBullet::Move(const CVector3D& offset)
{
	CBullet::Move(offset);
}

void CNormalBullet::Draw()
{
	putimage_alpha_zoom(static_cast<int>(m_position.GetX()), static_cast<int>(m_position.GetY()), m_scale, CNormalBulletFC::GetInstance()->GetImg(m_normal_bullet_type));
}

GET_SET_FUN_DEFINE(CNormalBullet::ENormalBulletType, CNormalBullet, m_normal_bullet_type, NormalBulletType)
