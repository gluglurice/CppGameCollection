#pragma once

#include "CSoldier.h"

class CArcher : public CSoldier
{
public:

	using CSoldier::CSoldier;

	CArcher(const Position& position, const std::wstring& img_path);

	void Attack(CSoldier** enemies, int target_id, int enemy_num) override;

	void GotAttackedBy(float damage) override;
};
