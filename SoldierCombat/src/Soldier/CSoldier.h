#pragma once

#include <iostream>
#include <string>
#include <Utils/Utils.h>

#include "CActor.h"

class CSoldier : public CActor
{
GET_SET_FUN_DECLAR(int, m_hp, HP)

GET_SET_FUN_DECLAR(int, m_atk, ATK)

GET_SET_FUN_DECLAR(std::string, m_name, Name)

public:

	CSoldier();

	CSoldier(const Position& position, const std::wstring& img_path);

	~CSoldier();

	virtual void Attack(CSoldier& other);

	virtual void GotAttackedBy(CSoldier& other);
};
