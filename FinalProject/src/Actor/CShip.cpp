#include "CShip.h"

CShip::CShip() {}

CShip::CShip(const CActor::Position& position, const EShipType& ship_type) : CActor(position), m_ship_type(ship_type)
{
	switch (m_ship_type)
	{
	case CShip::EShipType::ST_PLAYER:
		m_direction = CShip::DEFAULT_PLAYER_DIRECTION;
		break;
	case CShip::EShipType::ST_ENEMY:
		m_direction = CShip::DEFAULT_ENEMY_DIRECTION;
		break;
	}

	m_velocity = CShip::DEFAULT_VELOCITY;

	m_hp = CShip::DEFAULT_MAX_HP;
	m_max_hp = CShip::DEFAULT_MAX_HP;
	m_mp = CShip::DEFAULT_MAX_MP;
	m_max_mp = CShip::DEFAULT_MAX_MP;
	m_bullet_type = CShip::DEFAULT_BULLET_TYPE;
	m_skill = CShip::DEFAULT_SKILL;
}

CShip::~CShip() {}

void CShip::Move(int move_x, int move_y)
{

}

void CShip::Shoot()
{

}

void CShip::UseSkill()
{

}

void CShip::Die()
{

}

void CShip::Draw()
{

}

GET_SET_FUN_DEFINE(CShip::EShipType, CShip, m_ship_type, ShipType)
GET_SET_FUN_DEFINE(int, CShip, m_hp, HP)
GET_SET_FUN_DEFINE(int, CShip, m_max_hp, MaxHP)
GET_SET_FUN_DEFINE(int, CShip, m_mp, MP)
GET_SET_FUN_DEFINE(int, CShip, m_max_mp, MaxMP)
GET_SET_FUN_DEFINE(CBullet::EBulletType, CShip, m_bullet_type, BulletType)
GET_SET_FUN_DEFINE(CShip::EShipSkill, CShip, m_skill, Skill)
