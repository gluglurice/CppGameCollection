#pragma once

#include <iostream>
#include <string>

#include "src/Utils/Utils.h"

class CHero
{
	GET_SET_FUN_DECLAR(int, m_hp, HP)

	GET_SET_FUN_DECLAR(std::string, m_name, Name)

public:

	CHero();

	~CHero();

	virtual void Say();
};
