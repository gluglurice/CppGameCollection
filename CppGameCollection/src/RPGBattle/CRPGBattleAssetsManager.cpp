#include "CRPGBattleAssetsManager.h"

const std::wstring CRPGBattleAssetsManager::UI_IMG_PATHS[UI_IMG_NUM] = {
	L"assets/RPGBattle/imgs/ui/ui_background.png",
	L"assets/RPGBattle/imgs/ui/keyboard_space.png",
};

const std::wstring CRPGBattleAssetsManager::MAP_BATTLE_PATH = {
	L"assets/RPGBattle/tiles/map_battle.txt" 
};

const std::wstring CRPGBattleAssetsManager::MAP_IMG_PATHS[MAP_IMG_NUM] = {
	L"assets/RPGBattle/imgs/terrain/terrain_flat.png",
	L"assets/RPGBattle/imgs/terrain/terrain_grass.png",
	L"assets/RPGBattle/imgs/terrain/terrain_flower.png",
};

const std::wstring CRPGBattleAssetsManager::ROLE_IMG_PATHS[ROLE_IMG_NUM] = {
	L"assets/RPGBattle/imgs/roles/enemy_gun.png",
	L"assets/RPGBattle/imgs/roles/enemy_gun_got_attacked.png",
	L"assets/RPGBattle/imgs/roles/enemy_sword.png",
	L"assets/RPGBattle/imgs/roles/enemy_sword_got_attacked.png",
	L"assets/RPGBattle/imgs/roles/hero.png",
	L"assets/RPGBattle/imgs/roles/hero_got_attacked.png",
};

CRPGBattleAssetsManager::CRPGBattleAssetsManager() {}

CRPGBattleAssetsManager::~CRPGBattleAssetsManager() {}

void  CRPGBattleAssetsManager::LoadUIAssets()
{
	for (int i = 0; i < UI_IMG_NUM; i++)
	{
		loadimage(&m_ui_imgs[i], UI_IMG_PATHS[i].c_str());
	}
}

void CRPGBattleAssetsManager::LoadMapAssets()
{
	for (int i = 0; i < MAP_IMG_NUM; i++)
	{
		loadimage(&m_map_imgs[i], MAP_IMG_PATHS[i].c_str());
	}
}

void CRPGBattleAssetsManager::LoadRoleAssets()
{
	for (int i = 0; i < ROLE_IMG_NUM; i++)
	{
		loadimage(&m_role_imgs[i], ROLE_IMG_PATHS[i].c_str());
	}
}

void CRPGBattleAssetsManager::LoadAssets()
{
	LoadUIAssets();
	LoadMapAssets();
	LoadRoleAssets();
}

IMAGE* CRPGBattleAssetsManager::GetUIImgs()
{
	return m_ui_imgs;
}

void CRPGBattleAssetsManager::SetUIImgs(IMAGE* ui_imgs)
{
	for (int i = 0; i < UI_IMG_NUM; i++)
	{
		this->m_ui_imgs[i] = ui_imgs[i];
	}
}

IMAGE* CRPGBattleAssetsManager::GetMapImgs()
{
	return m_map_imgs;
}

void CRPGBattleAssetsManager::SetMapImgs(IMAGE* map_imgs)
{
	for (int i = 0; i < MAP_IMG_NUM; i++)
	{
		this->m_map_imgs[i] = map_imgs[i];
	}
}

IMAGE* CRPGBattleAssetsManager::GetRoleImgs()
{
	return m_role_imgs;
}

void CRPGBattleAssetsManager::SetRoleImgs(IMAGE* role_imgs)
{
	for (int i = 0; i < ROLE_IMG_NUM; i++)
	{
		this->m_role_imgs[i] = role_imgs[i];
	}
}
