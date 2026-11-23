#pragma once

#include "Bullet.h"

class CBomb : public CBullet
{
public:
	enum EBombType
	{
		BT_SINGLE,
		BT_DOUBLE,
	};

GET_SET_FUN_DECLAR(EBombType, m_bomb_type, BombType)
GET_SET_FUN_DECLAR(float, m_acceleration, Acceleration)

public:
	CBomb();

	CBomb(const CVector3D& center, const CVector3D& position, const CVector3D& rotation, const CVector3D& scale, int tile_size, CActor::EDirection direction, float velocity, const EBulletFrom& bullet_from, const EBombType& bomb_type, float acceleration);

	~CBomb();

	void Move(const CVector3D& offset) override;

	void Destroy() override;

	void Draw() override;
};
