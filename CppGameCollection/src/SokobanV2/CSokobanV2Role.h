#pragma once

#include <string>

#include <graphics.h>

#include "src/Utils/Utils.h"

class CSokobanV2Map;

class CSokobanV2Role
{
public:
	struct Position
	{
		int x;
		int y;
	};

	enum RoleDirection
	{
		RD_DOWN,
		RD_LEFT,
		RD_RIGHT,
		RD_UP,
	};

private:
	Position m_position;
	RoleDirection m_direction;

public:
	/* Constructions */
	CSokobanV2Role();

	~CSokobanV2Role();

	CSokobanV2Role(Position position, RoleDirection direction);

	/* Logic methods */
	void Move(RoleDirection direction, int move_x, int move_y, CSokobanV2Map& map);

	/* Getters and setters */
	Position GetPosition();

	void SetPosition(Position position);

	RoleDirection GetDirection();

	void SetDirection(RoleDirection direction);
};
