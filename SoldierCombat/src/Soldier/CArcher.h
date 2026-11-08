#pragma once

#include "CSoldier.h"

class CArcher : public CSoldier
{
public:

	CArcher();

	CArcher(const Position& position, const std::wstring& img_path);

	~CArcher();

	void Attack(CSoldier& other) override;

	void GotAttackedBy(CSoldier& other) override;
};
