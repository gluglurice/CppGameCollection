#pragma once

#include "CBullet.h"

class CNormalBullet : public CBullet
{
public:
	enum ENormalBulletType
	{
		NBT_SINGLE,
		NBT_DOUBLE,
		NBT_TRIPLE,
	};

GET_SET_FUN_DECLAR(ENormalBulletType, m_normal_bullet_type, NormalBulletType)

public:
	CNormalBullet();

	CNormalBullet(const CVector3D& center, const CVector3D& position, const CVector3D& rotation, const CVector3D& scale, int tile_size, CActor::EDirection direction, float velocity, EBulletFrom bullet_from, ENormalBulletType normal_bullet_type);

	~CNormalBullet();

	void Move(const CVector3D& offset) override;

	void Draw() override;
};
