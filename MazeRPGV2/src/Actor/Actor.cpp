#include "Actor.h"

CActor::CActor() {}

CActor::CActor(D3DXVECTOR3 center, D3DXVECTOR3 position_logic, D3DXVECTOR3 position_render, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, int tile_size, Direction direction, float velocity)
	: m_center(center), m_position_logic(position_logic), m_position_render(position_render), m_rotation(rotation), m_scale(scale), m_tile_size(tile_size), m_direction(direction), m_velocity(velocity) {}

CActor::~CActor() {}

void CActor::Move(Direction direction)
{
	switch (direction)
	{
	case D_DOWN:
		m_position_render.y += m_velocity;
		break;
	case D_RIGHT:
		m_position_render.x += m_velocity;
		break;
	case D_UP:
		m_position_render.y -= m_velocity;
		break;
	case D_LEFT:
		m_position_render.x -= m_velocity;
		break;
	}
}

void CActor::Destroy()
{
	delete this;
}

void CActor::Draw() {}

GET_SET_FUN_DEFINE(D3DXVECTOR3, CActor, m_center, Center)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CActor, m_position_logic, PositionLogic)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CActor, m_position_render, PositionRender)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CActor, m_rotation, Rotation)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CActor, m_scale, Scale)
GET_SET_FUN_DEFINE(int, CActor, m_tile_size, TileSize)
GET_SET_FUN_DEFINE(CActor::Direction, CActor, m_direction, Direction)
GET_SET_FUN_DEFINE(float, CActor, m_velocity, Velocity)
