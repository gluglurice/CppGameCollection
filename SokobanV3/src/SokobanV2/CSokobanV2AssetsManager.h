#pragma once

#include <string>
#include <fstream>

#include <graphics.h>

class CSokobanV2AssetsManager
{
public:

	/* UI Related */
	static constexpr int SCALE = 2;
	static constexpr int TIP_BAR_WIDTH = 200;

	static constexpr int UI_IMG_NUM = 7;
	static const std::wstring UI_IMG_PATHS[UI_IMG_NUM];
	enum UIImg
	{
		UII_BACKGROUND,
		UII_KEYBOARD_W,
		UII_KEYBOARD_A,
		UII_KEYBOARD_S,
		UII_KEYBOARD_D,
		UII_KEYBOARD_SPACE,
		UII_TIPS,
	};

	/* Map Related */

	static constexpr int MAP_IMG_NUM = 5;
	static const std::wstring MAP_IMG_PATHS[MAP_IMG_NUM];
	enum MapElemImg
	{
		MEI_TERRAIN_GRASS,
		MEI_TERRAIN_WALL,
		MEI_TERRAIN_TARGET,
		MEI_TERRAIN_BOX,
		MEI_TERRAIN_BOX_IN_TARGET,
	};

	/* Role Related */

	static constexpr int ROLE_IMG_NUM = 4;
	static const std::wstring ROLE_IMG_PATHS[ROLE_IMG_NUM];
	enum RoleImg
	{
		RI_ROLE_DOWN,
		RI_ROLE_LEFT,
		RI_ROLE_RIGHT,
		RI_ROLE_UP,
	};

private:
	IMAGE m_ui_imgs[UI_IMG_NUM];
	IMAGE m_map_imgs[MAP_IMG_NUM];
	IMAGE m_role_imgs[ROLE_IMG_NUM];

public:
	/* Constructions */
	CSokobanV2AssetsManager();

	~CSokobanV2AssetsManager();

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
