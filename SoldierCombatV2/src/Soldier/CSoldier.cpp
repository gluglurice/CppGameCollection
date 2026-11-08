#include "CSoldier.h"

void CSoldier::Attack(CSoldier& other)
{
	other.GotAttackedBy(*this);
}

void CSoldier::GotAttackedBy(CSoldier& other)
{
	int damage = other.GetATK() > m_def ? other.GetATK() - m_def : 0;
	m_hp = m_hp > damage ? m_hp - damage : 0;
}

void CSoldier::Draw(const int scale)
{
	CActor::Draw(scale);
	settextcolor(WHITE);
	settextstyle(20, 0, L"Arial");

	outtextxy(m_position.x + 80, m_position.y + 200, std::wstring(m_name.begin(), m_name.end()).c_str());

	std::wstring hp_text = std::to_wstring(m_hp);
	for (int i = hp_text.length(); i < 3; ++i)
	{
		hp_text = L"0" + hp_text;
	}
	hp_text = L"HP: " + hp_text;
	outtextxy(m_position.x + 80, m_position.y + 220, hp_text.c_str());
}

GET_SET_FUN_DEFINE(int, CSoldier, m_max_hp, MaxHP)
GET_SET_FUN_DEFINE(int, CSoldier, m_hp, HP)
GET_SET_FUN_DEFINE(int, CSoldier, m_atk, ATK)
GET_SET_FUN_DEFINE(int, CSoldier, m_def, DEF)
GET_SET_FUN_DEFINE(std::string, CSoldier, m_name, Name)
