#pragma once

#include <string>

#include "src/Actor/CActor.h"

class CShip : public CActor
{
public:
	enum EShipType
	{
		ST_PLAYER,
		ST_ENEMY,
	};

	enum ENormalBulletType
	{
		NBT_SINGLE,
		NBT_DOUBLE,
		NBT_TRIPLE,
	};

	enum EBombType
	{
		BT_SINGLE,
		BT_DOUBLE,
	};

	static int SHIP_IMG_NUM;
	static  std::wstring SHIP_IMG_PATHS[];
	static  IMAGE SHIP_IMAGES[];

	static  CActor::EDirection DEFAULT_PLAYER_DIRECTION;
	static  CActor::EDirection DEFAULT_ENEMY_DIRECTION;
	static  float DEFAULT_VELOCITY;

	static  int DEFAULT_MAX_HP;
	static  int DEFAULT_MAX_MP;
	static  int DEFAULT_MAX_ATK;
	static  int DEFAULT_MAX_DEF;
	static  int DEFAULT_MAX_SHIELD;
	static  ENormalBulletType DEFAULT_NORMAL_BULLET_TYPE;
	static  EBombType DEFAULT_BOMB_TYPE;

	static void Init();

GET_SET_FUN_DECLAR(EShipType, m_ship_type, ShipType)
GET_SET_FUN_DECLAR(int, m_hp, HP)
GET_SET_FUN_DECLAR(int, m_max_hp, MaxHP)
GET_SET_FUN_DECLAR(int, m_mp, MP)
GET_SET_FUN_DECLAR(int, m_max_mp, MaxMP)
GET_SET_FUN_DECLAR(int, m_atk, Atk)
GET_SET_FUN_DECLAR(int, m_def, Def)
GET_SET_FUN_DECLAR(int, m_shield, Shield)
GET_SET_FUN_DECLAR(ENormalBulletType, m_normal_bullet_type, NormalBulletType)
GET_SET_FUN_DECLAR(EBombType, m_bomb_type, BombType)

public:
	CShip();

	CShip(const CActor::Position& position, const EShipType& ship_type);

	~CShip();

	void Move(int move_x, int move_y) override;

	void Shoot();

	void Bomb();

	void Die();

	void Draw() override;
};
