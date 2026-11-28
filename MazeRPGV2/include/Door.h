#pragma once

#include "Actor.h"

class CDoor : public CActor
{
public:
	enum Type
	{
		T_SINGLE,
		T_DOUBLE_LEFT,
		T_DOUBLE_RIGHT,
		T_COUNT,
	};

GET_SET_FUN_DECLAR(Type, m_type, Type)
GET_SET_FUN_DECLAR(bool, m_is_open, IsOpen)

public:
	CDoor();

	CDoor(CVector3D center, CVector3D position_logic, CVector3D position_render, CVector3D rotation, CVector3D scale, int tile_size, Direction direction, float velocity, State state, CActor::SpritesMap sprites, Type type, bool is_open);

	~CDoor();

	void UpdateCurSprite() override;

	void Update() override;

	void Idle() override;

	void Open();

	void Destroy() override;

	void Draw() override;
};
