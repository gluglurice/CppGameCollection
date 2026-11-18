#pragma once

#include "src/Actor/CActor.h"

class CItem : public CActor
{
public:
	enum EItemType
	{
		IT_HEALTH,
		IT_POWER,
		IT_SHIELD,
	};

	static int IMG_NUM;
	static  std::wstring* IMG_PATHS;
	static  IMAGE* IMGS;
	
	static float DEFAULT_VELOCITY;

	static void Init(const std::string& config_path);

	static void Delete();

GET_SET_FUN_DECLAR(EItemType, m_item_type, ItemType)

public:
	CItem();

	CItem(const CActor::Position& position, const EItemType& item_type);

	~CItem();

	void Move(int move_x, int move_y) override;

	void Draw() override;
};
