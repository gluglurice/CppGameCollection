#pragma once

#include "CSoldier.h"

class CLancer : public CSoldier
{
public:

	CLancer();

	~CLancer();

	void Attack(CSoldier& other) override;

	void GotAttackedBy(CSoldier& other) override;
};
