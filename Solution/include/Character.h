#pragma once

#include <Utils.h>
#include <Sprite.h>
#include <Graphic.h>

class CCharacter
{
public:
	enum State
	{
		S_IDLE,
		S_WALK,
	};

	enum Direction
	{
		D_DOWN,
		D_RIGHT,
		D_UP,
		D_LEFT,
	};

using SpriteMap = map<State, CSprite*>;

GET_SET_FUN_DECLAR(D3DXVECTOR3, m_center, Center)
GET_SET_FUN_DECLAR(D3DXVECTOR3, m_position, Position)
GET_SET_FUN_DECLAR(D3DXVECTOR3, m_rotation, Rotation)
GET_SET_FUN_DECLAR(D3DXVECTOR3, m_scale, Scale)
GET_SET_FUN_DECLAR(Direction, m_direction, Direction)

GET_SET_FUN_DECLAR(State, m_state, State)
GET_SET_FUN_DECLAR(SpriteMap, m_sprite_map, SpriteMap)

public:
	CCharacter();

	CCharacter(D3DXVECTOR3 center = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 rotation = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 scale = D3DXVECTOR3(1, 1, 1),
		Direction direction = D_RIGHT, State state = S_IDLE);

	void AddSprite(State state, CSprite* sprite);

	void UpdateState(State state);

	void Idle();

	void Move(const D3DXVECTOR3& offset);

	void Draw();
};
