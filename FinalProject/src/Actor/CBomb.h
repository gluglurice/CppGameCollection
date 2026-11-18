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

	static float DEFAULT_VELOCITY;
	static float DEFAULT_ACCELERATION;

	static void Init();

GET_SET_FUN_DECLAR(EBombType, m_bomb_type, BombType)
GET_SET_FUN_DECLAR(float, m_acceleration, Acceleration)

public:
	CBomb();

	CBomb(const CActor::Position& position, const EBulletFrom& bullet_from, const EBombType& bomb_type);

	~CBomb();

	void Move(int move_x, int move_y) override;

	void Draw() override;
};
