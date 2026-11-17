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
	
	static constexpr CActor::EDirection DEFAULT_DIRECTION = CActor::EDirection::D_DOWN;
	static constexpr float DEFAULT_VELOCITY = 0.2f;

GET_SET_FUN_DECLAR(EItemType, m_item_type, ItemType)

public:
	CItem();

	CItem(const CActor::Position& position, const EItemType& item_type);

	~CItem();

	void Move(int move_x, int move_y) override;

	void Draw() override;
};
