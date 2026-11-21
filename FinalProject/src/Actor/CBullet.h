#pragma once

#include "src/Actor/CActor.h"

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

	CBullet(const CVector3D& position, int tile_size, float scale, CActor::EDirection direction, float velocity, EBulletFrom bullet_from);

	~CBullet();

	void Move(const CVector3D& offset) override;

	void Draw() override;
};
