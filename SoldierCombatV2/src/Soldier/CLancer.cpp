#include "CLancer.h"

CLancer::CLancer(const Position& position, const std::wstring& img_path)
	: CSoldier(position, img_path)
{
	m_max_hp = 120;
	m_hp = 120;
	m_atk = 15;
	m_def = 10;
	m_name = "Lancer";
}

void CLancer::Attack(CSoldier& other)
{
	CSoldier::Attack(other);

	int damage = m_atk > other.GetDEF() ? m_atk - other.GetDEF() : 0;

	int heal = damage * 0.25;
	m_hp = m_hp + heal > m_max_hp ? m_max_hp : m_hp + heal;
}

void CLancer::GotAttackedBy(CSoldier& other)
{
	CSoldier::GotAttackedBy(other);
}
