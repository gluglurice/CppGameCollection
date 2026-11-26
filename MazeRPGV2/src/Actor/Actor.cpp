#include "Actor.h"

CActor::CActor() {}

CActor::CActor(CVector3D center, CVector3D position_logic, CVector3D position_render, CVector3D rotation, CVector3D scale, int tile_size, Direction direction, float velocity)
	: m_center(center), m_position_logic(position_logic), m_position_render(position_render), m_rotation(rotation), m_scale(scale), m_tile_size(tile_size), m_direction(direction), m_velocity(velocity) {}

CActor::~CActor() {}

void CActor::MoveRender(CVector3D offset)
{
	m_position_render += offset;
}

void CActor::MoveLogic(CVector3D offset)
{
	m_position_logic += offset;
}

void CActor::Destroy()
{
	delete this;
}

void CActor::Draw() {}

GET_SET_FUN_DEFINE(CVector3D, CActor, m_center, Center)
GET_SET_FUN_DEFINE(CVector3D, CActor, m_position_logic, PositionLogic)
GET_SET_FUN_DEFINE(CVector3D, CActor, m_position_render, PositionRender)
GET_SET_FUN_DEFINE(CVector3D, CActor, m_rotation, Rotation)
GET_SET_FUN_DEFINE(CVector3D, CActor, m_scale, Scale)
GET_SET_FUN_DEFINE(int, CActor, m_tile_size, TileSize)
GET_SET_FUN_DEFINE(CActor::Direction, CActor, m_direction, Direction)
GET_SET_FUN_DEFINE(float, CActor, m_velocity, Velocity)
