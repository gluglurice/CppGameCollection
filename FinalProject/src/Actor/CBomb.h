#pragma once

#include "CBullet.h"

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

	CBomb(const CVector3D& position, int tile_size, float scale, CActor::EDirection direction, float velocity, const EBulletFrom& bullet_from, const EBombType& bomb_type, float acceleration);

	~CBomb();

	void Move(const CVector3D& offset) override;

	void Draw() override;
};
