#include "CSokobanV2Role.h"
#include "CSokobanV2Map.h"

CSokobanV2Role::CSokobanV2Role() {}

CSokobanV2Role::~CSokobanV2Role() {}

CSokobanV2Role::CSokobanV2Role(Position position, RoleDirection direction) : m_position(position), m_direction(direction) {}

void CSokobanV2Role::Move(RoleDirection direction, int move_x, int move_y, CSokobanV2Map& map)
{
	m_direction = direction;
	int role_x_new = m_position.x + move_x;
	int role_y_new = m_position.y + move_y;

	/* Move box */
	if (map.GetMapElem(role_y_new, role_x_new) == CSokobanV2Map::ME_TERRAIN_BOX)
	{
		int box_x_new = role_x_new + move_x;
		int box_y_new = role_y_new + move_y;

		if (map.GetMapElem(box_y_new, box_x_new) == CSokobanV2Map::ME_TERRAIN_WALL
			|| map.GetMapElem(box_y_new, box_x_new) == CSokobanV2Map::ME_TERRAIN_BOX
			|| map.GetMapElem(box_y_new, box_x_new) == CSokobanV2Map::ME_TERRAIN_BOX_IN_TARGET)
		{
			return;
		}

		if (map.GetMapElem(box_y_new, box_x_new) == CSokobanV2Map::ME_TERRAIN_GRASS)
		{
			map.SetMapElem(role_y_new, role_x_new, CSokobanV2Map::ME_TERRAIN_GRASS);
			map.SetMapElem(box_y_new, box_x_new, CSokobanV2Map::ME_TERRAIN_BOX);
		}

		if (map.GetMapElem(box_y_new, box_x_new) == CSokobanV2Map::ME_TERRAIN_TARGET)
		{
			map.SetMapElem(role_y_new, role_x_new, CSokobanV2Map::ME_TERRAIN_GRASS);
			map.SetMapElem(box_y_new, box_x_new, CSokobanV2Map::ME_TERRAIN_BOX_IN_TARGET);
			map.SetBoxNotInTargetNum(map.GetBoxNotInTargetNum() - 1);
		}
	}

	/* Move box in target */
	if (map.GetMapElem(role_y_new, role_x_new) == CSokobanV2Map::ME_TERRAIN_BOX_IN_TARGET)
	{
		int box_x_new = role_x_new + move_x;
		int box_y_new = role_y_new + move_y;

		if (map.GetMapElem(box_y_new, box_x_new) == CSokobanV2Map::ME_TERRAIN_WALL
			|| map.GetMapElem(box_y_new, box_x_new) == CSokobanV2Map::ME_TERRAIN_BOX
			|| map.GetMapElem(box_y_new, box_x_new) == CSokobanV2Map::ME_TERRAIN_BOX_IN_TARGET)
		{
			return;
		}

		if (map.GetMapElem(box_y_new, box_x_new) == CSokobanV2Map::ME_TERRAIN_GRASS)
		{
			map.SetMapElem(role_y_new, role_x_new, CSokobanV2Map::ME_TERRAIN_TARGET);
			map.SetMapElem(box_y_new, box_x_new, CSokobanV2Map::ME_TERRAIN_BOX);
			map.SetBoxNotInTargetNum(map.GetBoxNotInTargetNum() + 1);
		}

		if (map.GetMapElem(box_y_new, box_x_new) == CSokobanV2Map::ME_TERRAIN_TARGET)
		{
			map.SetMapElem(role_y_new, role_x_new, CSokobanV2Map::ME_TERRAIN_TARGET);
			map.SetMapElem(box_y_new, box_x_new, CSokobanV2Map::ME_TERRAIN_BOX_IN_TARGET);
		}
	}

	/* Move in non-wall areas */
	if (map.GetMapElem(role_y_new, role_x_new) != CSokobanV2Map::ME_TERRAIN_WALL)
	{
		m_position.x = role_x_new;
		m_position.y = role_y_new;
	}
}

CSokobanV2Role::Position CSokobanV2Role::GetPosition()
{
	return m_position;
}

void CSokobanV2Role::SetPosition(Position position)
{
	m_position = position;
}

CSokobanV2Role::RoleDirection CSokobanV2Role::GetDirection()
{
	return m_direction;
}

void CSokobanV2Role::SetDirection(RoleDirection direction)
{
	m_direction = direction;
}
