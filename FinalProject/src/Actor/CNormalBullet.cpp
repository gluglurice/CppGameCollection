#include "CNormalBullet.h"

#include "CNormalBulletFC.h"

CNormalBullet::CNormalBullet() {}

CNormalBullet::CNormalBullet(const CVector3D& center, const CVector3D& position, const CVector3D& rotation, const CVector3D& scale, int tile_size, CActor::EDirection direction, float velocity, EBulletFrom bullet_from, ENormalBulletType normal_bullet_type)
	: CBullet(center, position, rotation, scale, tile_size, direction, velocity, bullet_from), m_normal_bullet_type(normal_bullet_type) {}

CNormalBullet::~CNormalBullet() {}

void CNormalBullet::Move(const CVector3D& offset)
{
	CBullet::Move(offset);
}

void CNormalBullet::Draw()
{
	CGraphic::GetInstance()->DrawTex(*CNormalBulletFC::GetInstance()->GetImg(m_normal_bullet_type), m_position, m_center, m_rotation, m_scale);
}

GET_SET_FUN_DEFINE(CNormalBullet::ENormalBulletType, CNormalBullet, m_normal_bullet_type, NormalBulletType)
