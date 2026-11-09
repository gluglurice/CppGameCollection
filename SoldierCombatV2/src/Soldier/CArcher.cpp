#include "CArcher.h"

CArcher::CArcher(const Position& position, const std::wstring& img_path)
	: CSoldier(position, img_path)
{
	m_max_hp = 4000;
	m_hp = 4000;
	m_atk = 101;
	m_def = 19;
	m_name = new wchar_t[]( L"孙尚香");
}

void CArcher::Attack(CSoldier** enemies, int target_id, int enemy_num)
{
	if (rand() % 100 < 35)
	{
		for (int i = 0; i < enemy_num; ++i)
		{
			if (i == target_id)
			{
				outtextxy(400, 30, (std::wstring(m_name) + L" 使用主动技能【瞄准】，" + L" 向 " + enemies[i]->GetName() + L" 使出致命一击！").c_str());
				enemies[i]->GotAttackedBy(m_atk * 3);
				Sleep(1000);
			}
			else
			{
				outtextxy(400, 30, (std::wstring(m_name) + L" 使用主动技能【瞄准】，" + L" 对 " + enemies[i]->GetName() + L" 造成扩散伤害！").c_str());
				enemies[i]->GotAttackedBy(m_atk);
				Sleep(1000);
			}
		}
	}
	else
	{
		outtextxy(400, 30, (std::wstring(m_name) + L" 向 " + enemies[target_id]->GetName() + L" 发起了攻击！").c_str());
		enemies[target_id]->GotAttackedBy(m_atk);
	}
}

void CArcher::GotAttackedBy(float damage)
{
	CSoldier::GotAttackedBy(damage);
}
