#include "CShip.h"

#include <EasyXExtension.h>

#include "CshipFC.h"
#include "CBullet.h"
#include "CNormalBullet.h"
#include "CNormalBulletFC.h"

CShip::CShip() {}

CShip::CShip(const CVector3D& position, int tile_size, float scale, EDirection direction, float velocity, EShipCamp ship_camp, EShipType ship_type, int hp, int max_hp, int mp, int max_mp, int atk, float firing_rate, int def, int shield, ENormalBulletType normal_bullet_type, EBombType bomb_type)
	: CActor(position, tile_size, scale, direction, velocity), m_ship_camp(ship_camp), m_ship_type(ship_type), m_hp(hp), m_max_hp(max_hp), m_mp(mp), m_max_mp(max_mp), m_atk(atk), m_firing_rate(firing_rate), m_def(def), m_shield(shield), m_normal_bullet_type(normal_bullet_type), m_bomb_type(bomb_type) {}

CShip::~CShip() {}

void CShip::Move(const CVector3D& offset)
{
	CActor::Move(offset);
}

void CShip::Shoot()
{
	CNormalBullet* bullet = CNormalBulletFC::GetInstance()->CreateNormalBullet(m_position, static_cast<CBullet::EBulletFrom>(m_ship_camp), static_cast<CNormalBullet::ENormalBulletType>(m_normal_bullet_type));
	m_normal_bullets.push_back(bullet);
}

void CShip::Bomb()
{

}

void CShip::Die()
{

}

void CShip::Draw()
{
	putimage_alpha_zoom(static_cast<int>(m_position.GetX()), static_cast<int>(m_position.GetY()), m_scale, CShipFC::GetInstance()->GetImg(m_ship_type));
	for (CNormalBullet* bullet : m_normal_bullets)
	{
		bullet->Draw();
	}
}

GET_SET_FUN_DEFINE(CShip::EShipCamp, CShip, m_ship_camp, ShipCamp)
GET_SET_FUN_DEFINE(CShip::EShipType, CShip, m_ship_type, ShipType)
GET_SET_FUN_DEFINE(int, CShip, m_hp, HP)
GET_SET_FUN_DEFINE(int, CShip, m_max_hp, MaxHP)
GET_SET_FUN_DEFINE(int, CShip, m_mp, MP)
GET_SET_FUN_DEFINE(int, CShip, m_max_mp, MaxMP)
GET_SET_FUN_DEFINE(int, CShip, m_atk, Atk)
GET_SET_FUN_DEFINE(float, CShip, m_firing_rate, FiringRate)
GET_SET_FUN_DEFINE(int, CShip, m_def, Def)
GET_SET_FUN_DEFINE(int, CShip, m_shield, Shield)
GET_SET_FUN_DEFINE(CShip::ENormalBulletType, CShip, m_normal_bullet_type, NormalBulletType)
GET_SET_FUN_DEFINE(CShip::EBombType, CShip, m_bomb_type, BombType)
GET_SET_FUN_DEFINE(std::vector<CNormalBullet*>, CShip, m_normal_bullets, NormalBullets)
