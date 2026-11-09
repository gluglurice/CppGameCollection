#include "CSoldier.h"

CSoldier::~CSoldier()
{
	delete[] m_name;
}

void CSoldier::Attack(CSoldier** enemies, int target_id, int enemy_num)
{
	outtextxy(400, 30, (std::wstring(m_name) + L" 向 " + enemies[target_id]->GetName() + L" 发起了攻击！").c_str());
	enemies[target_id]->GotAttackedBy(m_atk);
}

void CSoldier::GotAttackedBy(float damage)
{
	int final_damage = damage > m_def ? damage - m_def : 0;
	m_hp = m_hp > final_damage ? m_hp - final_damage : 0;
	outtextxy(400, 50, ( L" 造成了 " + std::to_wstring(final_damage) + L" 点伤害！" ).c_str());
}

void CSoldier::Draw(const int scale)
{
	CActor::Draw(scale);
	settextcolor(WHITE);

	outtextxy(m_position.x + 80, m_position.y + 160, m_name);

	std::wstring hp_text = std::to_wstring(static_cast<int>(m_hp));
	for (int i = hp_text.length(); i < 3; ++i)
	{
		hp_text = L"0" + hp_text;
	}
	hp_text = L"HP: " + hp_text;
	outtextxy(m_position.x + 80, m_position.y + 180, hp_text.c_str());
}

GET_SET_FUN_DEFINE(float, CSoldier, m_max_hp, MaxHP)
GET_SET_FUN_DEFINE(float, CSoldier, m_hp, HP)
GET_SET_FUN_DEFINE(float, CSoldier, m_atk, ATK)
GET_SET_FUN_DEFINE(float, CSoldier, m_def, DEF)
GET_SET_FUN_DEFINE(wchar_t*, CSoldier, m_name, Name)
