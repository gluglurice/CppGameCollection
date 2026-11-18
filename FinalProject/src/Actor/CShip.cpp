#include "CShip.h"

#include "src/Game/CGame.h"

int CShip::SHIP_IMG_NUM = 1;
std::wstring CShip::SHIP_IMG_PATHS[] = { L""};
IMAGE CShip::SHIP_IMAGES[] = { NULL };

CActor::EDirection CShip::DEFAULT_PLAYER_DIRECTION = CActor::EDirection::D_UP;
CActor::EDirection CShip::DEFAULT_ENEMY_DIRECTION = CActor::EDirection::D_DOWN;
float CShip::DEFAULT_VELOCITY = 1.0f;

int CShip::DEFAULT_MAX_HP = 100;
int CShip::DEFAULT_MAX_MP = 100;
int CShip::DEFAULT_MAX_ATK = 1;
int CShip::DEFAULT_MAX_DEF = 0;
int CShip::DEFAULT_MAX_SHIELD = 0;
CShip::ENormalBulletType CShip::DEFAULT_NORMAL_BULLET_TYPE = CShip::ENormalBulletType::NBT_SINGLE;
CShip::EBombType CShip::DEFAULT_BOMB_TYPE = CShip::EBombType::BT_SINGLE;

void CShip::Init()
{

}

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
	m_atk = CShip::DEFAULT_MAX_ATK;
	m_def = CShip::DEFAULT_MAX_DEF;
	m_shield = CShip::DEFAULT_MAX_SHIELD;
	m_normal_bullet_type = CShip::DEFAULT_NORMAL_BULLET_TYPE;
	m_bomb_type = CShip::DEFAULT_BOMB_TYPE;
}

CShip::~CShip() {}

void CShip::Move(int move_x, int move_y)
{

}

void CShip::Shoot()
{

}

void CShip::Bomb()
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
GET_SET_FUN_DEFINE(int, CShip, m_atk, Atk)
GET_SET_FUN_DEFINE(int, CShip, m_def, Def)
GET_SET_FUN_DEFINE(int, CShip, m_shield, Shield)
GET_SET_FUN_DEFINE(CShip::ENormalBulletType, CShip, m_normal_bullet_type, NormalBulletType)
GET_SET_FUN_DEFINE(CShip::EBombType, CShip, m_bomb_type, BombType)
