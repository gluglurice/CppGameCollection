#pragma once

#include <iostream>
#include <string>

#include <Utils/Utils.h>

#include "CActor.h"

class CSoldier : public CActor
{
public:

	enum SoldierType
	{
		ARCHER,
		LANCER,
		HEAVY_ARMORED,
	};

GET_SET_FUN_DECLAR(float, m_max_hp, MaxHP)
GET_SET_FUN_DECLAR(float, m_hp, HP)
GET_SET_FUN_DECLAR(float, m_atk, ATK)
GET_SET_FUN_DECLAR(float, m_def, DEF)
GET_SET_FUN_DECLAR(wchar_t*, m_name, Name)

public:

	using CActor::CActor;

	~CSoldier();

	virtual void Attack(CSoldier** enemies, int target_id, int enemy_num);

	virtual void GotAttackedBy(float damage);

	void Draw(const int scale) override;
};
