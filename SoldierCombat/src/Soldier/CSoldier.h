#pragma once

#include <iostream>
#include <string>

#include "src/Utils/Utils.h"

class CSoldier
{
	GET_SET_FUN_DECLAR(int, m_hp, HP)
	GET_SET_FUN_DECLAR(int, m_atk, ATK)
	GET_SET_FUN_DECLAR(std::string, m_name, Name)

public:

	CSoldier();

	~CSoldier();

	virtual void Attack(CSoldier& other);

	virtual void GotAttackedBy(CSoldier& other);
};
