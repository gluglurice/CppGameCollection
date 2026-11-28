#pragma once

#include "Actor.h"

class CCharacter : public CActor
{
public:
	enum Camp
	{
		T_PLAYER,
		T_ENEMY,
	};

GET_SET_FUN_DECLAR(Camp, m_camp, Camp)

public:
	CCharacter();

	CCharacter(CVector3D center, CVector3D position_logic, CVector3D position_render, CVector3D rotation, CVector3D scale, int tile_size, Direction direction, float velocity, State state, CActor::SpritesMap sprites, Camp camp);

	~CCharacter();

	void UpdateCurSprite() override;

	void UpdateState(State state, Direction direction) override;

	void Idle() override;

	void MoveRender(CVector3D offset) override;

	void MoveLogic(CVector3D offset) override;

	void Destroy() override;

	void Draw() override;
};
