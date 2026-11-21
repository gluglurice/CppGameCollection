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

GET_SET_FUN_DECLAR(EItemType, m_item_type, ItemType)

public:
	CItem();

	CItem(const CVector3D& position, int tile_size, float scale, CActor::EDirection direction, float velocity, const EItemType& item_type);

	~CItem();

	void Move(const CVector3D& offset) override;

	void Draw() override;
};
