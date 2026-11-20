#pragma once

#include <map>
#include <string>

#include "src/Actor/CNormalBullet.h"

class CNormalBulletFC
{
private:
	static CNormalBulletFC* m_instance;

public:
	static CNormalBulletFC* GetInstance();

private:
	std::map<CNormalBullet::ENormalBulletType, std::pair<CNormalBullet*, IMAGE*>> m_normal_bullet_map;

private:
	CNormalBulletFC();

public:
	~CNormalBulletFC();

	IMAGE* GetImg(CNormalBullet::ENormalBulletType normal_bullet_type);

	CNormalBullet* CreateNormalBullet(const CVector3D& position, CBullet::EBulletFrom bullet_from, CNormalBullet::ENormalBulletType normal_bullet_type);
};
