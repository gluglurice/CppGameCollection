#pragma once

#include "CSoldier.h"

class CLancer : public CSoldier
{
public:

	using CSoldier::CSoldier;

	CLancer(const Position& position, const std::wstring& img_path);

	void Attack(CSoldier& other) override;

	void GotAttackedBy(CSoldier& other) override;
};
