#pragma once

#include <string>
#include <fstream>

#include <graphics.h>

class CRPGBattleAssetsManager
{
public:

	/* UI Related */
	static constexpr int SCALE = 2;
	static constexpr int TIP_BAR_WIDTH = 200;

	static constexpr int UI_IMG_NUM = 2;
	static const std::wstring UI_IMG_PATHS[UI_IMG_NUM];
	enum UIImg
	{
		UII_BACKGROUND,
		UII_KEYBOARD_SPACE,
	};

	/* Map Related */

	static const std::wstring MAP_BATTLE_PATH;

	static constexpr int MAP_IMG_NUM = 3;
	static const std::wstring MAP_IMG_PATHS[MAP_IMG_NUM];
	enum MapElemImg
	{
		MEI_TERRAIN_FLAT,
		MEI_TERRAIN_GRASS,
		MEI_TERRAIN_FLOWER,
	};

	/* Role Related */

	static constexpr int ROLE_BATTLE_SIZE = 96;

	static constexpr int ROLE_IMG_NUM = 6;
	static const std::wstring ROLE_IMG_PATHS[ROLE_IMG_NUM];
	enum RoleImg
	{
		RI_ENEMY_GUN,
		RI_ENEMY_GUN_GOT_ATTACKED,
		RI_ENEMY_SWORD,
		RI_ENEMY_SWORD_GOT_ATTACKED,
		RI_HERO,
		RI_HERO_GOT_ATTACKED
	};

private:
	IMAGE m_ui_imgs[UI_IMG_NUM];
	IMAGE m_map_imgs[MAP_IMG_NUM];
	IMAGE m_role_imgs[ROLE_IMG_NUM];

public:
	/* Constructions */
	CRPGBattleAssetsManager();

	~CRPGBattleAssetsManager();

	/* Logic functions */

	void LoadUIAssets();

	void LoadMapAssets();

	void LoadRoleAssets();

	void LoadAssets();

	/* Getters and setters */
	IMAGE* GetUIImgs();

	void SetUIImgs(IMAGE* ui_imgs);

	IMAGE* GetMapImgs();

	void SetMapImgs(IMAGE* map_imgs);

	IMAGE* GetRoleImgs();

	void SetRoleImgs(IMAGE* role_imgs);
};
