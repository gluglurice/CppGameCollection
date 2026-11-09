#pragma once

#include "CSoldier.h"

class CHeavyArmored : public CSoldier
{
public:

	using CSoldier::CSoldier;

	CHeavyArmored(const Position& position, const std::wstring& img_path);

	void Attack(CSoldier** enemies, int target_id, int enemy_num) override;

	void GotAttackedBy(float damage) override;
};
