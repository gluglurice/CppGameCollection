#pragma once

#include <Vector/CVector3D.h>

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

	CNormalBullet(const CVector3D& position, int tile_size, float scale, CActor::EDirection direction, float velocity, EBulletFrom bullet_from, ENormalBulletType normal_bullet_type);

	~CNormalBullet();

	void Move(const CVector3D& offset) override;

	void Draw() override;
};
