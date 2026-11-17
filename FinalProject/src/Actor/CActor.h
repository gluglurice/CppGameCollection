#pragma once

#include <graphics.h>
#include <Utils/Utils.h>

class CActor
{
public:
	struct Position
	{
		int x;
		int y;
	};

	enum EDirection
	{
		D_UP,
		D_DOWN,
	};

	static constexpr EDirection DEFAULT_DIRECTION = EDirection::D_UP;
	static constexpr float DEFAULT_VELOCITY = 0.0f;

GET_SET_FUN_DECLAR(Position, m_position, Position)
GET_SET_FUN_DECLAR(EDirection, m_direction, Direction)
GET_SET_FUN_DECLAR(float, m_velocity, Velocity)

public:
	CActor();

	CActor(const Position& position);

	~CActor();

	virtual void Move(int move_x, int move_y);

	virtual void Draw();
};
