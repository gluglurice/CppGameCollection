#pragma once

#include "CNormalBullet.h"

class CNormalBulletFC : public CSingleton<CNormalBulletFC>
{
	/**
	 * @brief 友元化基类，便于基类指针调用派生类私有构造函数
	 */
	friend CSingleton<CNormalBulletFC>;

protected:
	static map<CNormalBullet::ENormalBulletType, pair<CNormalBullet*, Image*>> m_normal_bullet_map;

	CNormalBulletFC();

public:
	Image* GetImg(CNormalBullet::ENormalBulletType normal_bullet_type);

	CNormalBullet* CreateNormalBullet(const CVector3D& position, CBullet::EBulletFrom bullet_from, CNormalBullet::ENormalBulletType normal_bullet_type);
};
