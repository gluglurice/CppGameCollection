#include "CShip.h"

#include "CGame.h"
#include "CshipFC.h"
#include "CBullet.h"
#include "CNormalBullet.h"
#include "CNormalBulletFC.h"
#include <cmath>
#include <utility>

CShip::CShip() {}

CShip::CShip(const CVector3D& center, const CVector3D& position, const CVector3D& rotation, const CVector3D& scale, int tile_size, EDirection direction, float velocity, EShipCamp ship_camp, EShipType ship_type, int hp, int max_hp, int mp, int max_mp, int atk, float firing_rate, int def, int shield, ENormalBulletType normal_bullet_type, EBombType bomb_type)
	: CActor(center, position, rotation, scale, tile_size, direction, velocity), m_ship_camp(ship_camp), m_ship_type(ship_type), m_hp(hp), m_max_hp(max_hp), m_mp(mp), m_max_mp(max_mp), m_atk(atk), m_firing_rate(firing_rate), m_def(def), m_shield(shield), m_normal_bullet_type(normal_bullet_type), m_bomb_type(bomb_type) {}

CShip::~CShip() {}

void CShip::Move(const CVector3D& offset)
{
	CActor::Move(offset);
}

void CShip::Shoot()
{
	CVector3D bullet_position = m_position - CVector3D(0, m_center.y, 0);
	CNormalBullet* bullet = CNormalBulletFC::GetInstance()->CreateNormalBullet(bullet_position, static_cast<CBullet::EBulletFrom>(m_ship_camp), static_cast<CNormalBullet::ENormalBulletType>(m_normal_bullet_type));
	m_normal_bullets.push_back(bullet);
}

void CShip::Bomb()
{

}

void CShip::Destroy()
{
	for (CNormalBullet* bullet : m_normal_bullets)
	{
		bullet->Destroy();
	}
	CActor::Destroy();
}

void CShip::CheckAndDestroyNormalBullets()
{
	for (auto it = m_normal_bullets.begin(); it != m_normal_bullets.end(); )
	{
		CNormalBullet* bullet = *it;
		CVector3D bullet_position = bullet->GetPosition();
		CVector3D bullet_center = bullet->GetCenter();
		CVector3D bullet_rotation = bullet->GetRotation();
		CVector3D bullet_scale = bullet->GetScale();

		const float radians = bullet_rotation.z * 0.017453292519943295f;
		const float cos_angle = abs(cos(radians));
		const float sin_angle = abs(sin(radians));
		const float half_width = abs(bullet_center.x * bullet_scale.x);
		const float half_height = abs(bullet_center.y * bullet_scale.y);

		const float extent_x = half_width * cos_angle + half_height * sin_angle;
		const float extent_y = half_width * sin_angle + half_height * cos_angle;

		pair<CVector3D, CVector3D> bullet_outline = make_pair(
			CVector3D(bullet_position.x - extent_x, bullet_position.y - extent_y, bullet_position.z),
			CVector3D(bullet_position.x + extent_x, bullet_position.y + extent_y, bullet_position.z)
		);

		if (bullet_outline.first.y < 0 || bullet_outline.second.y > CGame::GRAPH_HEIGHT || bullet_outline.first.x < 0 || bullet_outline.second.x > CGame::GRAPH_WIDTH)
		{
			bullet->Destroy();
			it = m_normal_bullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void CShip::Draw()
{
	CGraphic::GetInstance()->DrawTex(*CShipFC::GetInstance()->GetImg(m_ship_type), m_position, m_center, m_rotation, m_scale);
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
GET_SET_FUN_DEFINE(list<CNormalBullet*>, CShip, m_normal_bullets, NormalBullets)
