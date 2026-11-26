#pragma once

#include <Utils.h>
#include <Graphic.h>
#include <Sprite.h>
#include <Vector3D.h>

class CActor
{
public:
	enum Direction
	{
		D_DOWN,
		D_RIGHT,
		D_UP,
		D_LEFT,
		D_COUNT,
	};

GET_SET_FUN_DECLAR(CVector3D, m_center, Center)
GET_SET_FUN_DECLAR(CVector3D, m_position_logic, PositionLogic)
GET_SET_FUN_DECLAR(CVector3D, m_position_render, PositionRender)
GET_SET_FUN_DECLAR(CVector3D, m_rotation, Rotation)
GET_SET_FUN_DECLAR(CVector3D, m_scale, Scale)
GET_SET_FUN_DECLAR(int, m_tile_size, TileSize)
GET_SET_FUN_DECLAR(Direction, m_direction, Direction)
GET_SET_FUN_DECLAR(float, m_velocity, Velocity)

public:
	CActor();

	CActor(CVector3D center, CVector3D position_logic, CVector3D position_render, CVector3D rotation, CVector3D scale, int tile_size, Direction direction, float velocity);

	~CActor();

	virtual void MoveRender(CVector3D offset);

	virtual void MoveLogic(CVector3D offset);

	virtual void Destroy();

	virtual void Draw();
};
