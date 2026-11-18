#include "CSokobanV2AssetsManager.h"

const std::wstring CSokobanV2AssetsManager::UI_IMG_PATHS[UI_IMG_NUM] = {
	L"assets/SokobanV2/imgs/ui/ui_background.png",
	L"assets/SokobanV2/imgs/ui/keyboard_w.png",
	L"assets/SokobanV2/imgs/ui/keyboard_a.png",
	L"assets/SokobanV2/imgs/ui/keyboard_s.png",
	L"assets/SokobanV2/imgs/ui/keyboard_d.png",
	L"assets/SokobanV2/imgs/ui/keyboard_space.png",
	L"assets/SokobanV2/imgs/ui/ui_tips.png",
};

const std::wstring CSokobanV2AssetsManager::MAP_IMG_PATHS[MAP_IMG_NUM] = {
	L"assets/SokobanV2/imgs/terrain/terrain_grass.png",
	L"assets/SokobanV2/imgs/terrain/terrain_wall.png",
	L"assets/SokobanV2/imgs/terrain/terrain_target.png",
	L"assets/SokobanV2/imgs/terrain/terrain_box.png",
	L"assets/SokobanV2/imgs/terrain/terrain_box_in_target.png",
};

const std::wstring CSokobanV2AssetsManager::ROLE_IMG_PATHS[ROLE_IMG_NUM] = {
	L"assets/SokobanV2/imgs/roles/role_down.png",
	L"assets/SokobanV2/imgs/roles/role_left.png",
	L"assets/SokobanV2/imgs/roles/role_right.png",
	L"assets/SokobanV2/imgs/roles/role_up.png",
};

CSokobanV2AssetsManager::CSokobanV2AssetsManager() {}

CSokobanV2AssetsManager::~CSokobanV2AssetsManager() {}

void  CSokobanV2AssetsManager::LoadUIAssets()
{
	for (int i = 0; i < UI_IMG_NUM; i++)
	{
		loadimage(&m_ui_imgs[i], UI_IMG_PATHS[i].c_str());
	}
}

void CSokobanV2AssetsManager::LoadMapAssets()
{
	for (int i = 0; i < MAP_IMG_NUM; i++)
	{
		loadimage(&m_map_imgs[i], MAP_IMG_PATHS[i].c_str());
	}
}

void CSokobanV2AssetsManager::LoadRoleAssets()
{
	for (int i = 0; i < ROLE_IMG_NUM; i++)
	{
		loadimage(&m_role_imgs[i], ROLE_IMG_PATHS[i].c_str());
	}
}

void CSokobanV2AssetsManager::LoadAssets()
{
	LoadUIAssets();
	LoadMapAssets();
	LoadRoleAssets();
}

IMAGE* CSokobanV2AssetsManager::GetUIImgs()
{
	return m_ui_imgs;
}

void CSokobanV2AssetsManager::SetUIImgs(IMAGE* ui_imgs)
{
	for (int i = 0; i < UI_IMG_NUM; i++)
	{
		this->m_ui_imgs[i] = ui_imgs[i];
	}
}

IMAGE* CSokobanV2AssetsManager::GetMapImgs()
{
	return m_map_imgs;
}

void CSokobanV2AssetsManager::SetMapImgs(IMAGE* map_imgs)
{
	for (int i = 0; i < MAP_IMG_NUM; i++)
	{
		this->m_map_imgs[i] = map_imgs[i];
	}
}

IMAGE* CSokobanV2AssetsManager::GetRoleImgs()
{
	return m_role_imgs;
}

void CSokobanV2AssetsManager::SetRoleImgs(IMAGE* role_imgs)
{
	for (int i = 0; i < ROLE_IMG_NUM; i++)
	{
		this->m_role_imgs[i] = role_imgs[i];
	}
}
