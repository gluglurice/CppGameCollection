#include "Actor.h"

CActor::CActor() {}

CActor::CActor(D3DXVECTOR3 center, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, int tile_size, Direction direction, float velocity)
	: m_center(center), m_position(position), m_rotation(rotation), m_scale(scale), m_tile_size(tile_size), m_direction(direction), m_velocity(velocity) {}

CActor::~CActor() {}

void CActor::Move(D3DXVECTOR3 offset)
{
	m_position += offset;
}

void CActor::Destroy()
{
	delete this;
}

void CActor::Draw() {}

GET_SET_FUN_DEFINE(D3DXVECTOR3, CActor, m_center, Center)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CActor, m_position, Position)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CActor, m_rotation, Rotation)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CActor, m_scale, Scale)
GET_SET_FUN_DEFINE(int, CActor, m_tile_size, TileSize)
GET_SET_FUN_DEFINE(CActor::Direction, CActor, m_direction, Direction)
GET_SET_FUN_DEFINE(float, CActor, m_velocity, Velocity)
