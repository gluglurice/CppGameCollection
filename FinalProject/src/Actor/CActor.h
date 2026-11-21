#pragma once

#include <tinyxml.h>
#include <Utils.h>
#include <Vector3D.h>
#include <EasyXExtension.h>

class CActor
{
public:
	enum EDirection
	{
		D_UP,
		D_DOWN,
	};

GET_SET_FUN_DECLAR(CVector3D, m_position, Position)
GET_SET_FUN_DECLAR(int, m_tile_size, TileSize)
GET_SET_FUN_DECLAR(float, m_scale, Scale)
GET_SET_FUN_DECLAR(EDirection, m_direction, Direction)
GET_SET_FUN_DECLAR(float, m_velocity, Velocity)

public:
	CActor();

	CActor(const CVector3D& position, int tile_size, float scale, EDirection direction, float velocity);

	~CActor();

	virtual void Move(const CVector3D& offset);

	virtual void Draw();
};
