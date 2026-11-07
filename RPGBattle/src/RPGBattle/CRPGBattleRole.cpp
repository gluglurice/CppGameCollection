#include "CRPGBattleRole.h"

CRPGBattleRole::CRPGBattleRole() {}

CRPGBattleRole::~CRPGBattleRole() {}

CRPGBattleRole::CRPGBattleRole(RoleType type, std::string name) : m_type(type), m_name(name)
{
	SetIsAlive(true);

	if (type == RT_HERO)
	{
		SetHP(100);
		SetATK(20);
		SetDEF(10);
	}
	else if (type == RT_ENEMY_SWORD)
	{
		SetHP(50);
		SetATK(15);
		SetDEF(5);
	}
	else if (type == RT_ENEMY_GUN)
	{
		SetHP(30);
		SetATK(25);
		SetDEF(3);
	}
}

void CRPGBattleRole::Attack(CRPGBattleRole& target)
{
	int damage = GetATK() - target.GetDEF();
	if (damage < 0)
	{
		damage = 0;
	}
	target.SetHP(target.GetHP() - damage);
	if (target.GetHP() <= 0)
	{
		target.SetIsAlive(false);
	}
}

bool CRPGBattleRole::GetIsAlive()
{
	return m_is_alive;
}

void CRPGBattleRole::SetIsAlive(bool is_alive)
{
	m_is_alive = is_alive;
}

CRPGBattleRole::RoleType CRPGBattleRole::GetType()
{
	return m_type;
}

void CRPGBattleRole::SetType(CRPGBattleRole::RoleType type)
{
	m_type = type;
}

std::string CRPGBattleRole::GetName()
{
	return m_name;
}

void CRPGBattleRole::SetName(std::string name)
{
	m_name = name;
}

int CRPGBattleRole::GetHP()
{
	return m_hp;
}

void CRPGBattleRole::SetHP(int hp)
{
	m_hp = hp;
}

int CRPGBattleRole::GetATK()
{
	return m_atk;
}

void CRPGBattleRole::SetATK(int atk)
{
	m_atk = atk;
}

int CRPGBattleRole::GetDEF()
{
	return m_def;
}

void CRPGBattleRole::SetDEF(int def)
{
	m_def = def;
}
