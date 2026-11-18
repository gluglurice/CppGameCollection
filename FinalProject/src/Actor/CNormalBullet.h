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

	static int IMG_NUM;
	static  std::wstring* IMG_PATHS;
	static  IMAGE* IMGS;

	static float DEFAULT_VELOCITY;

	static void Init(const std::string& config_path);

	static void Delete();

GET_SET_FUN_DECLAR(ENormalBulletType, m_normal_bullet_type, NormalBulletType)

public:
	CNormalBullet();

	CNormalBullet(const CActor::Position& position, const EBulletFrom& bullet_from, const ENormalBulletType& normal_bullet_type);

	~CNormalBullet();

	void Move(int move_x, int move_y) override;

	void Draw() override;
};
