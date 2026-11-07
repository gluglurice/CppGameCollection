#pragma once

#include "CSoldier.h"

class CHeavyArmored : public CSoldier
{
public:

	CHeavyArmored();

	~CHeavyArmored();

	void Attack(CSoldier& other) override;

	void GotAttackedBy(CSoldier& other) override;
};
