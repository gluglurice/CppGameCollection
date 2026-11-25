#pragma once

#include <Sprite.h>

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

	CCharacter(D3DXVECTOR3 center, D3DXVECTOR3 position_logic, D3DXVECTOR3 position_render, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, int tile_size, Direction direction, float velocity, Type type, State state, vector<CSprite*> sprites);

	~CCharacter();

	void UpdateState(State state, Direction direction);

	void Idle();

	void Move(Direction direction) override;

	void Destroy() override;

	void Draw() override;
};
