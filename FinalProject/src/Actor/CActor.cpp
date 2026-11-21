#include "CActor.h"

CActor::CActor() {}

CActor::CActor(const CVector3D& position, int tile_size, float scale, EDirection direction, float velocity) : m_position(position), m_tile_size(tile_size), m_scale(scale), m_direction(direction), m_velocity(velocity) {}

CActor::~CActor() {}

void CActor::Move(const CVector3D& offset)
{
	m_position += offset;
}

void CActor::Draw() {}

GET_SET_FUN_DEFINE(CVector3D, CActor, m_position, Position)
GET_SET_FUN_DEFINE(int, CActor, m_tile_size, TileSize)
GET_SET_FUN_DEFINE(float, CActor, m_scale, Scale)
GET_SET_FUN_DEFINE(CActor::EDirection, CActor, m_direction, Direction)
GET_SET_FUN_DEFINE(float, CActor, m_velocity, Velocity)
