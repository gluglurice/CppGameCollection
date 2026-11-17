#include "CRole.h"

const int CRole::ROLE_IMG_NUM = 1;
const std::wstring CRole::ROLE_IMG_PATHS[CRole::ROLE_IMG_NUM] = {
	L"assets/imgs/role/role.png"
};
IMAGE CRole::ROLE_IMGS[CRole::ROLE_IMG_NUM];

const int CRole::ATTRIBUTE_IMG_NUM = 1;
const std::wstring CRole::ATTRIBUTE_IMG_PATHS[CRole::ATTRIBUTE_IMG_NUM] = {
	L"assets/imgs/ui/attributes.png"
};
IMAGE CRole::ATTRIBUTE_IMGS[CRole::ATTRIBUTE_IMG_NUM];

const int CRole::UI_IMG_NUM = 5;
const std::wstring CRole::UI_IMG_PATHS[CRole::UI_IMG_NUM] = {
	L"assets/imgs/ui/keyboard_w.png",
	L"assets/imgs/ui/keyboard_s.png",
	L"assets/imgs/ui/keyboard_a.png",
	L"assets/imgs/ui/keyboard_d.png",
	L"assets/imgs/ui/keyboard_space.png"
};
IMAGE CRole::UI_IMGS[CRole::UI_IMG_NUM];

void CRole::Init()
{
	for (int i = 0; i < ROLE_IMG_NUM; ++i)
	{
		loadimage(&ROLE_IMGS[i], ROLE_IMG_PATHS[i].c_str());
	}
	for (int i = 0; i < ATTRIBUTE_IMG_NUM; ++i)
	{
		loadimage(&ATTRIBUTE_IMGS[i], ATTRIBUTE_IMG_PATHS[i].c_str());
	}
	for (int i = 0; i < UI_IMG_NUM; ++i)
	{
		loadimage(&UI_IMGS[i], UI_IMG_PATHS[i].c_str());
	}
}

CRole::CRole() : m_name("Role"), m_hp(1000), m_max_hp(1000), m_mp(1000), m_max_mp(1000), m_atk(100), m_def(100) {}

CRole::CRole(const std::string& name, int hp, int max_hp, int mp, int max_mp, int atk, int def)
	: m_name(name), m_hp(hp), m_max_hp(max_hp), m_mp(mp), m_max_mp(max_mp), m_atk(atk), m_def(def) {}

CRole::~CRole()
{
	for (auto& item_pair : m_bag.GetItems())
	{
		delete item_pair.second;
	}
	for (auto& equipment_pair : m_bag.GetEquipments())
	{
		delete equipment_pair.second;
	}
}

void CRole::AddItem(CItem* item)
{
	m_bag.AddItem(item);
}

void CRole::RemoveItem(CItem* item)
{
	m_bag.RemoveItem(item);
}

void CRole::UseDrug(CDrug* drug)
{
	switch (drug->GetDrugType())
	{
	case CDrug::EDrugType::DT_HEAL:
		m_hp = min(m_max_hp, m_hp + drug->GetHP());
		break;
	case CDrug::EDrugType::DT_MANA:
		m_mp = min(m_max_mp, m_mp + drug->GetMP());
		break;
	case CDrug::EDrugType::DT_BUFF_ATK:
		m_atk += drug->GetATK();
		break;
	case CDrug::EDrugType::DT_BUFF_DEF:
		m_def += drug->GetDEF();
		break;
	}
	RemoveItem(drug);
}

void CRole::Equip(CEquipment* equipment)
{
	m_bag.Equip(equipment);

	m_max_hp += equipment->GetHP();
	m_hp += equipment->GetHP();
	m_max_mp += equipment->GetMP();
	m_mp += equipment->GetMP();
	m_atk += equipment->GetATK();
	m_def += equipment->GetDEF();
}

void CRole::UnEquip(CEquipment::EEquipmentType equipment_type)
{
	CEquipment* equipment = m_bag.GetEquipments()[equipment_type];

	m_max_hp -= equipment->GetHP();
	m_hp -= equipment->GetHP();
	m_max_mp -= equipment->GetMP();
	m_mp -= equipment->GetMP();
	m_atk -= equipment->GetATK();
	m_def -= equipment->GetDEF();

	m_bag.UnEquip(equipment_type);
}

void CRole::ChooseItem(int index)
{
	m_bag.SetItemChosenIndex(index);
}

void CRole::ChooseEquipment(int index)
{
	m_bag.SetEquipmentChosenIndex(index);
}

void CRole::Draw()
{
	setbkmode(TRANSPARENT);
	settextcolor(RGB(0x6D, 0x4B, 0x27));
	settextstyle(20, 0, _T("微软雅黑"), 0, 0, FW_BOLD, FALSE, FALSE, FALSE);

	/* 绘制角色和属性面板背景 */
	putimage_alpha_zoom(0, 0, 1, &ATTRIBUTE_IMGS[0]);
	putimage_alpha_zoom(200, 0, 1, &ROLE_IMGS[0]);

	/* 绘制角色属性 */
	const int ATTRIBUTE_KEY_WIDTH = 32;
	const int ATTRIBUTE_KEY_HEIGHT = 64;
	const int ATTRIBUTE_KEY_TERMINAL = 32;

	outtextxy(
		ATTRIBUTE_KEY_WIDTH,
		ATTRIBUTE_KEY_HEIGHT,
		(L"HP：" + std::to_wstring(m_hp) + L" / " + std::to_wstring(m_max_hp)).c_str()
	);
	outtextxy(
		ATTRIBUTE_KEY_WIDTH,
		ATTRIBUTE_KEY_HEIGHT + ATTRIBUTE_KEY_TERMINAL,
		(L"MP：" + std::to_wstring(m_mp) + L" / " + std::to_wstring(m_max_mp)).c_str()
	);
	outtextxy(
		ATTRIBUTE_KEY_WIDTH,
		ATTRIBUTE_KEY_HEIGHT + ATTRIBUTE_KEY_TERMINAL * 2,
		(L"ATK：" + std::to_wstring(m_atk)).c_str()
	);
	outtextxy(
		ATTRIBUTE_KEY_WIDTH,
		ATTRIBUTE_KEY_HEIGHT + ATTRIBUTE_KEY_TERMINAL * 3,
		(L"DEF：" + std::to_wstring(m_def)).c_str()
	);

	/* 绘制UI按键 */
	const int UI_KEY_SCALE = 2;
	const int UI_KEY_SIZE = 32;
	const int UI_KEY_WIDTH_MID = 70;
	const int UI_KEY_HEIGHT = 540;

	putimage_alpha_zoom(
		UI_KEY_WIDTH_MID,
		UI_KEY_HEIGHT,
		UI_KEY_SCALE,
		&UI_IMGS[0]
	);
	putimage_alpha_zoom(
		UI_KEY_WIDTH_MID,
		UI_KEY_HEIGHT + UI_KEY_SIZE + 16,
		UI_KEY_SCALE,
		&UI_IMGS[1]
	);
	putimage_alpha_zoom(
		UI_KEY_WIDTH_MID - UI_KEY_SIZE - 16,
		UI_KEY_HEIGHT + UI_KEY_SIZE + 16,
		UI_KEY_SCALE,
		&UI_IMGS[2]
	);
	putimage_alpha_zoom(
		UI_KEY_WIDTH_MID + UI_KEY_SIZE + 16,
		UI_KEY_HEIGHT + UI_KEY_SIZE + 16,
		UI_KEY_SCALE,
		&UI_IMGS[3]
	);
	outtextxy(
		UI_KEY_WIDTH_MID,
		UI_KEY_HEIGHT + UI_KEY_SIZE * UI_KEY_SCALE * 2 - 16,
		_T("移动光标")
	);

	putimage_alpha_zoom(
		UI_KEY_WIDTH_MID - 54,
		UI_KEY_HEIGHT + UI_KEY_SIZE * UI_KEY_SCALE * 2 + 16,
		UI_KEY_SCALE,
		&UI_IMGS[4]
	);
	outtextxy(
		UI_KEY_WIDTH_MID,
		UI_KEY_HEIGHT + UI_KEY_SIZE * UI_KEY_SCALE * 3 + 16,
		_T("使用物品")
	);

	m_bag.Draw();
}

GET_SET_FUN_DEFINE(CBag, CRole, m_bag, Bag)
GET_SET_FUN_DEFINE(int, CRole, m_hp, HP)
GET_SET_FUN_DEFINE(int, CRole, m_max_hp, MaxHP)
GET_SET_FUN_DEFINE(int, CRole, m_mp, MP)
GET_SET_FUN_DEFINE(int, CRole, m_max_mp, MaxMP)
GET_SET_FUN_DEFINE(int, CRole, m_atk, ATK)
GET_SET_FUN_DEFINE(int, CRole, m_def, DEF)
GET_SET_FUN_DEFINE(std::string, CRole, m_name, Name)
