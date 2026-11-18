#include "CDrug.h"

CDrug::CDrug() {}

CDrug::CDrug(int id, const std::string& name, EItemType item_type, EDrugType drug_type, int hp, int mp, int atk, int def)
	: CItem(id, name, item_type, hp, mp, atk, def), m_drug_type(drug_type) {}

CDrug::~CDrug() {}

GET_SET_FUN_DEFINE(CDrug::EDrugType, CDrug, m_drug_type, DrugType)
