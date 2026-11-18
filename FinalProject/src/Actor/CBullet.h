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

	static CActor::EDirection DEFAULT_PLAYER_DIRECTION;
	static CActor::EDirection DEFAULT_ENEMY_DIRECTION;

	static void Init();

GET_SET_FUN_DECLAR(EBulletFrom, m_bullet_from, BulletFrom)

public:
	CBullet();

	CBullet(const CActor::Position& position, const EBulletFrom& bullet_from);

	~CBullet();

	void Move(int move_x, int move_y) override;

	void Draw() override;
};
