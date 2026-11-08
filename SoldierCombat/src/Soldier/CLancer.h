#pragma once

#include "CSoldier.h"

class CLancer : public CSoldier
{
public:

	CLancer();

	CLancer(const Position& position, const std::wstring& img_path);

	~CLancer();

	void Attack(CSoldier& other) override;

	void GotAttackedBy(CSoldier& other) override;
};
