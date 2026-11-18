#include "CShip.h"

int CShip::IMG_NUM;
std::wstring* CShip::IMG_PATHS;
IMAGE* CShip::IMGS;

CActor::EDirection CShip::DEFAULT_PLAYER_DIRECTION;
CActor::EDirection CShip::DEFAULT_ENEMY_DIRECTION;
float CShip::DEFAULT_VELOCITY;

int CShip::DEFAULT_MAX_HP;
int CShip::DEFAULT_MAX_MP;
int CShip::DEFAULT_MAX_ATK;
int CShip::DEFAULT_MAX_DEF;
int CShip::DEFAULT_MAX_SHIELD;
CShip::ENormalBulletType CShip::DEFAULT_NORMAL_BULLET_TYPE;
CShip::EBombType CShip::DEFAULT_BOMB_TYPE;

void CShip::Init(const std::string& config_path)
{
	CShip::IMG_NUM = 1;
	CShip::IMG_PATHS = new std::wstring[CShip::IMG_NUM];
	CShip::IMG_PATHS[0] = L"assets/img/ship/ship_blue_s.png";
	CShip::IMGS = new IMAGE[CShip::IMG_NUM];
	loadimage(&CShip::IMGS[0], CShip::IMG_PATHS[0].c_str());

	CShip::DEFAULT_PLAYER_DIRECTION = CActor::EDirection::D_UP;
	CShip::DEFAULT_ENEMY_DIRECTION = CActor::EDirection::D_DOWN;
	CShip::DEFAULT_VELOCITY = 1.0f;

	CShip::DEFAULT_MAX_HP = 100;
	CShip::DEFAULT_MAX_MP = 100;
	CShip::DEFAULT_MAX_ATK = 1;
	CShip::DEFAULT_MAX_DEF = 0;
	CShip::DEFAULT_MAX_SHIELD = 0;
	CShip::DEFAULT_NORMAL_BULLET_TYPE = CShip::ENormalBulletType::NBT_SINGLE;
	CShip::DEFAULT_BOMB_TYPE = CShip::EBombType::BT_SINGLE;
}

void CShip::Delete()
{
	if (CShip::IMG_PATHS)
	{
		delete[] CShip::IMG_PATHS;
		CShip::IMG_PATHS = nullptr;
	}
	if (CShip::IMGS)
	{
		delete[] CShip::IMGS;
		CShip::IMGS = nullptr;
	}
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
