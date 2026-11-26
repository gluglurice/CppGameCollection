#pragma once

#include "Actor.h"

class CCharacter : public CActor
{
public:
	enum Type
	{
		T_PLAYER,
		T_ENEMY,
	};

	enum State
	{
		S_IDLE,
		S_WALK,
		S_COUNT,
	};

GET_SET_FUN_DECLAR(Type, m_type, Type)
GET_SET_FUN_DECLAR(State, m_state, State)
GET_SET_FUN_DECLAR(vector<CSprite*>, m_sprites, Sprites)

public:
	CCharacter();

	CCharacter(CVector3D center, CVector3D position_logic, CVector3D position_render, CVector3D rotation, CVector3D scale, int tile_size, Direction direction, float velocity, Type type, State state, vector<CSprite*> sprites);

	~CCharacter();

	void UpdateState(State state, Direction direction);

	void Idle();

	void MoveRender(CVector3D offset) override;

	void MoveLogic(CVector3D offset) override;

	void Destroy() override;

	void Draw() override;
};
