#pragma once

#include <Utils.h>
#include <Graphic.h>

class CActor
{
public:
	enum Direction
	{
		D_DOWN,
		D_RIGHT,
		D_UP,
		D_LEFT,
	};

GET_SET_FUN_DECLAR(D3DXVECTOR3, m_center, Center)
GET_SET_FUN_DECLAR(D3DXVECTOR3, m_position, Position)
GET_SET_FUN_DECLAR(D3DXVECTOR3, m_rotation, Rotation)
GET_SET_FUN_DECLAR(D3DXVECTOR3, m_scale, Scale)
GET_SET_FUN_DECLAR(int, m_tile_size, TileSize)
GET_SET_FUN_DECLAR(Direction, m_direction, Direction)
GET_SET_FUN_DECLAR(float, m_velocity, Velocity)

public:
	CActor();

	CActor(D3DXVECTOR3 center, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, int tile_size, Direction direction, float velocity);

	~CActor();

	virtual void Move(D3DXVECTOR3 offset);

	virtual void Destroy();

	virtual void Draw();
};
