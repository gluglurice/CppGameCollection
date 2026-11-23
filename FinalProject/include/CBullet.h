#pragma once

#include "CActor.h"

class CBullet : public CActor
{
public:
	enum EBulletFrom
	{
		BF_PLAYER,
		BF_ENEMY,
	};

GET_SET_FUN_DECLAR(EBulletFrom, m_bullet_from, BulletFrom)

public:
	CBullet();

	CBullet(const CVector3D& center, const CVector3D& position, const CVector3D& rotation, const CVector3D& scale, int tile_size, CActor::EDirection direction, float velocity, EBulletFrom bullet_from);

	~CBullet();

	void Move(const CVector3D& offset) override;

	void Destroy() override;

	void Draw() override;
};
