#include "CNormalBullet.h"

int CNormalBullet::IMG_NUM;
std::wstring* CNormalBullet::IMG_PATHS;
IMAGE* CNormalBullet::IMGS;

float CNormalBullet::DEFAULT_VELOCITY;

void CNormalBullet::Init(const std::string& config_path)
{
	CNormalBullet::IMG_NUM = 1;
	CNormalBullet::IMG_PATHS = new std::wstring[CNormalBullet::IMG_NUM];
	CNormalBullet::IMGS = new IMAGE[CNormalBullet::IMG_NUM];

	CNormalBullet::DEFAULT_VELOCITY = 5.0f;
}

void CNormalBullet::Delete()
{
	if (CNormalBullet::IMG_PATHS)
	{
		delete[] CNormalBullet::IMG_PATHS;
		CNormalBullet::IMG_PATHS = nullptr;
	}
	if (CNormalBullet::IMGS)
	{
		delete[] CNormalBullet::IMGS;
		CNormalBullet::IMGS = nullptr;
	}
}

CNormalBullet::CNormalBullet() {}

CNormalBullet::CNormalBullet(const CActor::Position& position, const EBulletFrom& bullet_from, const ENormalBulletType& normal_bullet_type)
	: CBullet(position, bullet_from), m_normal_bullet_type(normal_bullet_type)
{
	m_velocity = CNormalBullet::DEFAULT_VELOCITY;
}

CNormalBullet::~CNormalBullet() {}

void CNormalBullet::Move(int move_x, int move_y)
{

}

void CNormalBullet::Draw()
{

}

GET_SET_FUN_DEFINE(CNormalBullet::ENormalBulletType, CNormalBullet, m_normal_bullet_type, NormalBulletType)
