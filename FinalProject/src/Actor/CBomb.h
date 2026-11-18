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

	static int IMG_NUM;
	static  std::wstring* IMG_PATHS;
	static  IMAGE* IMGS;

	static float DEFAULT_VELOCITY;
	static float DEFAULT_ACCELERATION;

	static void Init(const std::string& config_path);

	static void Delete();

GET_SET_FUN_DECLAR(EBombType, m_bomb_type, BombType)
GET_SET_FUN_DECLAR(float, m_acceleration, Acceleration)

public:
	CBomb();

	CBomb(const CActor::Position& position, const EBulletFrom& bullet_from, const EBombType& bomb_type);

	~CBomb();

	void Move(int move_x, int move_y) override;

	void Draw() override;
};
