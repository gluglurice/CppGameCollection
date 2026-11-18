#include "CDrug.h"

const int CDrug::DRUG_IMG_NUM = 4;
const std::wstring CDrug::DRUG_IMG_PATHS[CDrug::DRUG_IMG_NUM] = {
	L"assets/imgs/item/drug_heal.png",
	L"assets/imgs/item/drug_mana.png",
	L"assets/imgs/item/drug_buff_atk.png",
	L"assets/imgs/item/drug_buff_def.png",
};
IMAGE CDrug::DRUG_IMGS[CDrug::DRUG_IMG_NUM];

void CDrug::Init()
{
	for (int i = 0; i < DRUG_IMG_NUM; ++i)
	{
		loadimage(&DRUG_IMGS[i], DRUG_IMG_PATHS[i].c_str());
	}
}

CDrug::CDrug() {}

CDrug::CDrug(int id, const std::string& name, EItemType item_type, EDrugType drug_type, int hp, int mp, int atk, int def)
	: CItem(id, name, item_type, hp, mp, atk, def), m_drug_type(drug_type) {}

CDrug::~CDrug() {}

GET_SET_FUN_DEFINE(CDrug::EDrugType, CDrug, m_drug_type, DrugType)
