#pragma once

#include "CSoldier.h"

class CHeavyArmored : public CSoldier
{
public:

	using CSoldier::CSoldier;

	CHeavyArmored(const Position& position, const std::wstring& img_path);

	void Attack(CSoldier& other) override;

	void GotAttackedBy(CSoldier& other) override;
};
