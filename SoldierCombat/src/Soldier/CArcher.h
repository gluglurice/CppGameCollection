#pragma once

#include "CSoldier.h"

class CArcher : public CSoldier
{
public:

	CArcher();

	~CArcher();

	void Attack(CSoldier& other) override;

	void GotAttackedBy(CSoldier& other) override;
};
