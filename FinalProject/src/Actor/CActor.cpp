#include "CActor.h"

CActor::EDirection CActor::DEFAULT_DIRECTION;
float CActor::DEFAULT_VELOCITY;

void CActor::Init(const std::string& config_path)
{
	CActor::DEFAULT_DIRECTION = CActor::EDirection::D_UP;
	CActor::DEFAULT_VELOCITY = 0.0f;
}

void CActor::Delete() {}

CActor::CActor() {}

CActor::CActor(const Position& position) : m_position(position), m_direction(CActor::DEFAULT_DIRECTION), m_velocity(CActor::DEFAULT_VELOCITY) {}

CActor::~CActor() {}

void CActor::Move(int move_x, int move_y)
{
	m_position.x += move_x;
	m_position.y += move_y;
}

void CActor::Draw()
{

}

GET_SET_FUN_DEFINE(CActor::Position, CActor, m_position, Position)
GET_SET_FUN_DEFINE(CActor::EDirection, CActor, m_direction, Direction)
GET_SET_FUN_DEFINE(float, CActor, m_velocity, Velocity)
