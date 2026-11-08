#include "CHeavyArmored.h"

CHeavyArmored::CHeavyArmored(const Position& position, const std::wstring& img_path)
	: CSoldier(position, img_path)
{
	m_max_hp = 150;
	m_hp = 150;
	m_atk = 12;
	m_def = 15;
	m_name = "Heavy Armored";
}

void CHeavyArmored::Attack(CSoldier& other)
{
	CSoldier::Attack(other);
}

void CHeavyArmored::GotAttackedBy(CSoldier& other)
{
	int damage = other.GetATK() > m_def ? other.GetATK() - m_def : 0;
	if (rand() % 100 < 40)
	{
		damage = damage * 0.4;
	}

	m_hp = m_hp > damage ? m_hp - damage : 0;
}
