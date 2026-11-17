#pragma once

#include "src/Actor/CActor.h"
#include "src/Actor/CBullet.h"

class CShip : public CActor
{
public:
	enum EShipType
	{
		ST_PLAYER,
		ST_ENEMY,
	};

	enum EShipSkill
	{
		SS_BOMB,
		SS_DOUBLE_BOMB,
	};

	static constexpr CActor::EDirection DEFAULT_PLAYER_DIRECTION = CActor::EDirection::D_UP;
	static constexpr CActor::EDirection DEFAULT_ENEMY_DIRECTION = CActor::EDirection::D_DOWN;
	static constexpr float DEFAULT_VELOCITY = 1.0f;

	static constexpr int DEFAULT_MAX_HP = 100;
	static constexpr int DEFAULT_MAX_MP = 100;
	static constexpr CBullet::EBulletType DEFAULT_BULLET_TYPE = CBullet::EBulletType::BT_SINGLE;
	static constexpr EShipSkill DEFAULT_SKILL = EShipSkill::SS_BOMB;

GET_SET_FUN_DECLAR(EShipType, m_ship_type, ShipType)
GET_SET_FUN_DECLAR(int, m_hp, HP)
GET_SET_FUN_DECLAR(int, m_max_hp, MaxHP)
GET_SET_FUN_DECLAR(int, m_mp, MP)
GET_SET_FUN_DECLAR(int, m_max_mp, MaxMP)
GET_SET_FUN_DECLAR(CBullet::EBulletType, m_bullet_type, BulletType)
GET_SET_FUN_DECLAR(EShipSkill, m_skill, Skill)

public:
	CShip();

	CShip(const CActor::Position& position, const EShipType& ship_type);

	~CShip();

	void Move(int move_x, int move_y) override;

	void Shoot();

	void UseSkill();

	void Die();

	void Draw() override;
};
