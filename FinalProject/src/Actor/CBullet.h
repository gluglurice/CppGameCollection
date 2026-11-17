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

	enum EBulletType
	{
		BT_SINGLE,
		BT_DOUBLE,
		BT_TRIPLE,
	};

	static constexpr CActor::EDirection DEFAULT_PLAYER_DIRECTION = CActor::EDirection::D_UP;
	static constexpr CActor::EDirection DEFAULT_ENEMY_DIRECTION = CActor::EDirection::D_DOWN;
	static constexpr float DEFAULT_VELOCITY = 5.0f;

GET_SET_FUN_DECLAR(EBulletFrom, m_bullet_from, BulletFrom)
GET_SET_FUN_DECLAR(EBulletType, m_bullet_type, BulletType)

public:
	CBullet();

	CBullet(const CActor::Position& position, const EBulletFrom& bullet_from, const EBulletType& bullet_type);

	~CBullet();

	void Move(int move_x, int move_y) override;

	void Draw() override;
};
