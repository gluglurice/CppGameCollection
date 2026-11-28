#include "Actor.h"

#include "Game.h"

CActor::CActor() {}

CActor::CActor(CVector3D center, CVector3D position_logic, CVector3D position_render, CVector3D rotation, CVector3D scale, int tile_size, Direction direction, float velocity, State state, SpritesMap sprites)
	: m_center(center), m_position_logic(position_logic), m_position_render(position_render), m_target_position_render(position_render), m_rotation(rotation), m_scale(scale), m_tile_size(tile_size), m_direction(direction), m_velocity(velocity), m_state(state), m_sprites(sprites)
{
	UpdateCurSprite();
}

CActor::~CActor() {}

void CActor::UpdateCurSprite()
{
	m_cur_sprite = static_cast<int>(m_state) * static_cast<int>(CActor::Direction::D_COUNT) + static_cast<int>(m_direction);
}

void CActor::UpdateState(State state, Direction direction)
{
	m_sprites[m_cur_sprite]->SetIsVisible(false);
	m_state = state;
	m_direction = direction;
	UpdateCurSprite();
	m_sprites[m_cur_sprite]->SetIsVisible(true);
	m_sprites[m_cur_sprite]->SetPosition(m_position_render);
}

void CActor::Idle()
{
	m_sprites[m_cur_sprite]->SetPlayState(CSprite::PS_CYCLE_TERMINAL);
	m_sprites[m_cur_sprite]->Update(CGame::DELTA_TIME);
}

void CActor::MoveRender(CVector3D offset)
{
	m_position_render += offset;
	m_sprites[m_cur_sprite]->SetPlayState(CSprite::PS_CYCLE);
	m_sprites[m_cur_sprite]->SetPosition(m_position_render);
	m_sprites[m_cur_sprite]->Update(CGame::DELTA_TIME);
}

void CActor::MoveLogic(CVector3D offset)
{
	m_position_logic += offset;
}

void CActor::Destroy()
{
	delete this;
}

void CActor::Draw()
{
	int sprite_index = static_cast<int>(m_state) * static_cast<int>(CActor::Direction::D_COUNT) + static_cast<int>(m_direction);
	m_sprites[sprite_index]->Draw();
}

GET_SET_FUN_DEFINE(CVector3D, CActor, m_center, Center)
GET_SET_FUN_DEFINE(CVector3D, CActor, m_position_logic, PositionLogic)
GET_SET_FUN_DEFINE(CVector3D, CActor, m_position_render, PositionRender)
GET_SET_FUN_DEFINE(CVector3D, CActor, m_target_position_render, TargetPositionRender)
GET_SET_FUN_DEFINE(CVector3D, CActor, m_rotation, Rotation)
GET_SET_FUN_DEFINE(CVector3D, CActor, m_scale, Scale)
GET_SET_FUN_DEFINE(int, CActor, m_tile_size, TileSize)
GET_SET_FUN_DEFINE(CActor::Direction, CActor, m_direction, Direction)
GET_SET_FUN_DEFINE(float, CActor, m_velocity, Velocity)
GET_SET_FUN_DEFINE(CActor::State, CActor, m_state, State)
GET_SET_FUN_DEFINE(CActor::SpritesMap, CActor, m_sprites, Sprites)
GET_SET_FUN_DEFINE(int, CActor, m_cur_sprite, CurSprite)
