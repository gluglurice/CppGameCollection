#pragma once

#include "CSoldier.h"

class CHeavyArmored : public CSoldier
{
public:

	CHeavyArmored();

	CHeavyArmored(const Position& position, const std::wstring& img_path);

	~CHeavyArmored();

	void Attack(CSoldier& other) override;

	void GotAttackedBy(CSoldier& other) override;
};
