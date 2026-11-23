#include "CActor.h"

CActor::CActor() {}

CActor::CActor(const CVector3D& center, const CVector3D& position, const CVector3D& rotation, const CVector3D& scale, int tile_size, EDirection direction, float velocity) : m_center(center), m_position(position), m_rotation(rotation), m_scale(scale), m_tile_size(tile_size), m_direction(direction), m_velocity(velocity) {}

CActor::~CActor() {}

void CActor::Move(const CVector3D& offset)
{
	m_position += offset;
}

void CActor::Destroy()
{
	delete this;
}

void CActor::Draw() {}

GET_SET_FUN_DEFINE(CVector3D, CActor, m_center, Center)
GET_SET_FUN_DEFINE(CVector3D, CActor, m_position, Position)
GET_SET_FUN_DEFINE(CVector3D, CActor, m_rotation, Rotation)
GET_SET_FUN_DEFINE(CVector3D, CActor, m_scale, Scale)
GET_SET_FUN_DEFINE(int, CActor, m_tile_size, TileSize)
GET_SET_FUN_DEFINE(CActor::EDirection, CActor, m_direction, Direction)
GET_SET_FUN_DEFINE(float, CActor, m_velocity, Velocity)
