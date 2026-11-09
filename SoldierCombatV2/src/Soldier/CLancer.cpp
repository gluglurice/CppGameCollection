#include "CLancer.h"

CLancer::CLancer(const Position& position, const std::wstring& img_path)
	: CSoldier(position, img_path)
{
	m_max_hp = 4500;
	m_hp = 4500;
	m_atk = 110;
	m_def = 25;
	m_name = new wchar_t[](L"赵云");
	m_atk_rose_round = 0;
}

void CLancer::Attack(CSoldier** enemies, int target_id, int enemy_num)
{
	if (m_atk_rose_round > 0)
	{
		m_atk_rose_round--;
		outtextxy(400, 10, (std::wstring(m_name) + L" 激昂效果减少 1 回合！").c_str());
		if (m_atk_rose_round == 0)
		{
			m_atk /= 3;
			outtextxy(400, 10, (std::wstring(m_name) + L" 激昂效果结束，攻击力恢复正常！").c_str());
		}
	}

	if (rand() % 100 < 40 && m_atk_rose_round == 0)
	{
		m_atk *= 3;
		m_atk_rose_round = 3;
		outtextxy(400, 10, (std::wstring(m_name) + L" 使用主动技能【激昂】，攻击力提升 3 回合！").c_str());
	}

	CSoldier::Attack(enemies, target_id, enemy_num);
}

void CLancer::GotAttackedBy(float damage)
{
	CSoldier::GotAttackedBy(damage);
}

GET_SET_FUN_DEFINE(unsigned, CLancer, m_atk_rose_round, AtkRoseRound)
