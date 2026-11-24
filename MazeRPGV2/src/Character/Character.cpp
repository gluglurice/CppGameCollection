#include "Character.h"

CCharacter::CCharacter() {}

CCharacter::CCharacter(D3DXVECTOR3 center, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, Direction direction, State state)
	: m_center(center), m_position(position), m_rotation(rotation), m_scale(scale), m_direction(direction), m_state(state) {}

void CCharacter::AddSprite(State state, CSprite* sprite)
{
	sprite->SetCenter(m_center);
	sprite->SetPosition(m_position);
	sprite->SetRotation(m_rotation);
	sprite->SetScale(m_scale);
	m_sprite_map[state] = sprite;
}

void CCharacter::UpdateState(State state)
{
	m_sprite_map[m_state]->SetIsVisible(false);
	m_state = state;
	m_sprite_map[m_state]->SetIsVisible(true);
	m_sprite_map[m_state]->SetPosition(m_position);

	if (m_direction != static_cast<CCharacter::Direction>(m_sprite_map[m_state]->GetDefaultDirection()))
	{
		m_scale.x = -abs(m_scale.x);
		m_sprite_map[m_state]->SetScale(m_scale);
	}
	else
	{
		m_scale.x = abs(m_scale.x);
		m_sprite_map[m_state]->SetScale(m_scale);
	}
}

void CCharacter::Idle()
{
	m_sprite_map[m_state]->SetPlayState(CSprite::PS_CYCLE_TERMINAL);
	m_sprite_map[m_state]->Update();
}

void CCharacter::Move(const D3DXVECTOR3& offset)
{
	m_position += offset;
	m_sprite_map[m_state]->SetPosition(m_position);
	m_sprite_map[m_state]->SetPlayState(CSprite::PS_CYCLE);
	m_sprite_map[m_state]->Update();
}

void CCharacter::Draw()
{
	m_sprite_map[m_state]->Draw();
}

GET_SET_FUN_DEFINE(D3DXVECTOR3, CCharacter, m_center, Center)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CCharacter, m_position, Position)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CCharacter, m_rotation, Rotation)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CCharacter, m_scale, Scale)
GET_SET_FUN_DEFINE(CCharacter::Direction, CCharacter, m_direction, Direction)

GET_SET_FUN_DEFINE(CCharacter::State, CCharacter, m_state, State)
GET_SET_FUN_DEFINE(CCharacter::SpriteMap, CCharacter, m_sprite_map, SpriteMap)
