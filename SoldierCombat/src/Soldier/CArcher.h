#pragma once

#include "CSoldier.h"

class CArcher : public CSoldier
{
public:

	using CSoldier::CSoldier;

	CArcher(const Position& position, const std::wstring& img_path);

	void Attack(CSoldier& other) override;

	void GotAttackedBy(CSoldier& other) override;
};
