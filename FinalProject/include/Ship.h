#pragma once

#include "Actor.h"

class CNormalBullet;

class CShip : public CActor
{
public:
	enum EShipCamp
	{
		SC_PLAYER,
		SC_ENEMY,
	};

	enum EShipType
	{
		ST_BLUE_S,
		ST_BLUE_M,
		ST_BLUE_L,
		ST_RED_S,
		ST_RED_M,
		ST_RED_L,
		ST_GREEN_S,
		ST_GREEN_M,
		ST_GREEN_L,
		ST_YELLOW_S,
		ST_YELLOW_M,
		ST_YELLOW_L,
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

GET_SET_FUN_DECLAR(EShipCamp, m_ship_camp, ShipCamp)
GET_SET_FUN_DECLAR(EShipType, m_ship_type, ShipType)
GET_SET_FUN_DECLAR(int, m_hp, HP)
GET_SET_FUN_DECLAR(int, m_max_hp, MaxHP)
GET_SET_FUN_DECLAR(int, m_mp, MP)
GET_SET_FUN_DECLAR(int, m_max_mp, MaxMP)
GET_SET_FUN_DECLAR(int, m_atk, Atk)
GET_SET_FUN_DECLAR(float, m_firing_rate, FiringRate)
GET_SET_FUN_DECLAR(int, m_def, Def)
GET_SET_FUN_DECLAR(int, m_shield, Shield)
GET_SET_FUN_DECLAR(ENormalBulletType, m_normal_bullet_type, NormalBulletType)
GET_SET_FUN_DECLAR(EBombType, m_bomb_type, BombType)
GET_SET_FUN_DECLAR(list<CNormalBullet*>, m_normal_bullets, NormalBullets)

public:
	CShip();

	CShip(const CVector3D& center, const CVector3D& position, const CVector3D& rotation, const CVector3D& scale, int tile_size, EDirection direction, float velocity, EShipCamp ship_camp, EShipType ship_type, int hp, int max_hp, int mp, int max_mp, int atk, float firing_rate, int def, int shield, ENormalBulletType normal_bullet_type, EBombType bomb_type);

	~CShip();

	void Move(const CVector3D& offset) override;

	void Shoot();

	void Bomb();

	void Destroy() override;

	void CheckAndDestroyNormalBullets();

	void Draw() override;
};
