#pragma once

#include "CSoldier.h"

class CLancer : public CSoldier
{
GET_SET_FUN_DECLAR(unsigned, m_atk_rose_round, AtkRoseRound)

public:

	using CSoldier::CSoldier;

	CLancer(const Position& position, const std::wstring& img_path);

	void Attack(CSoldier** enemies, int target_id, int enemy_num) override;

	void GotAttackedBy(float damage) override;
};
