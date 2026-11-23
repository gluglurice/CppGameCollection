#pragma once

#include <Utils.h>
#include <Graphic.h>
#include <Vector3D.h>

class CActor
{
public:
	enum EDirection
	{
		D_UP,
		D_DOWN,
	};

GET_SET_FUN_DECLAR(CVector3D, m_center, Center)
GET_SET_FUN_DECLAR(CVector3D, m_position, Position)
GET_SET_FUN_DECLAR(CVector3D, m_rotation, Rotation)
GET_SET_FUN_DECLAR(CVector3D, m_scale, Scale)
GET_SET_FUN_DECLAR(int, m_tile_size, TileSize)
GET_SET_FUN_DECLAR(EDirection, m_direction, Direction)
GET_SET_FUN_DECLAR(float, m_velocity, Velocity)

public:
	CActor();

	CActor(const CVector3D& center, const CVector3D& position, const CVector3D& rotation, const CVector3D& scale, int tile_size, EDirection direction, float velocity);

	~CActor();

	virtual void Move(const CVector3D& offset);

	virtual void Draw();
};
