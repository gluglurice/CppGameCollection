#pragma once

#include "CItem.h"

class CDrug : public CItem
{
public:
	enum EDrugType
	{
		DT_HEAL,
		DT_MANA,
		DT_BUFF_ATK,
		DT_BUFF_DEF,
		DT_COUNT,
	};

	static const int DRUG_IMG_NUM;
	static const std::wstring DRUG_IMG_PATHS[];
	static IMAGE DRUG_IMGS[];

	static void Init();

GET_SET_FUN_DECLAR(EDrugType, m_drug_type, DrugType)

public:
	CDrug();

	CDrug(int id, const std::string& name, EItemType item_type, EDrugType drug_type, int hp, int mp, int atk, int def);

	~CDrug();
};
