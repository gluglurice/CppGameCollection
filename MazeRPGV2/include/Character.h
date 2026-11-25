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
	};

using SpriteMap = map<State, CSprite*>;

GET_SET_FUN_DECLAR(Type, m_type, Type)
GET_SET_FUN_DECLAR(State, m_state, State)
GET_SET_FUN_DECLAR(SpriteMap, m_sprite_map, SpriteMap)

public:
	CCharacter();

	CCharacter(D3DXVECTOR3 center, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, int tile_size, Direction direction, float velocity, Type type, State state, SpriteMap sprite_map);

	~CCharacter();

	void SetSpriteReadMode(State state, CSprite::ReadMode read_mode, int play_row, int play_col, int row_num, int col_num);

	void UpdateState(State state);

	void Idle();

	void Move(D3DXVECTOR3 offset) override;

	void Destroy() override;

	void Draw() override;
};
