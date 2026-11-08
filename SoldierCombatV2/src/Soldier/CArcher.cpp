#include "CArcher.h"

CArcher::CArcher(const Position& position, const std::wstring& img_path)
	: CSoldier(position, img_path)
{
	m_max_hp = 100;
	m_hp = 100;
	m_atk = 20;
	m_def = 5;
	m_name = "Archer";
}

void CArcher::Attack(CSoldier& other)
{
	CSoldier::Attack(other);

	if (rand() % 100 < 40)
	{
		CSoldier::Attack(other);
	}
}

void CArcher::GotAttackedBy(CSoldier& other)
{
	CSoldier::GotAttackedBy(other);
}
