#include "CHeavyArmored.h"

CHeavyArmored::CHeavyArmored(const Position& position, const std::wstring& img_path)
	: CSoldier(position, img_path)
{
	m_max_hp = 4500;
	m_hp = 4500;
	m_atk = 90;
	m_def = 28;
	m_name = new wchar_t[](L"高顺");
}

void CHeavyArmored::Attack(CSoldier** enemies, int target_id, int enemy_num)
{
	if (rand() % 100 < 50)
	{
		float heal = m_max_hp * 0.1;
		m_hp = m_hp + heal > m_max_hp ? m_max_hp : m_hp + heal;
		outtextxy(400, 10, (std::wstring(m_name) + L" 使用主动技能【回复】，回复了 " + std::to_wstring(static_cast<int>(heal)) + L" 点生命值！").c_str());
	}
	CSoldier::Attack(enemies, target_id, enemy_num);
}

void CHeavyArmored::GotAttackedBy(float damage)
{
	CSoldier::GotAttackedBy(damage);
}
