#include "Character.h"

CCharacter::CCharacter() {}

CCharacter::CCharacter(D3DXVECTOR3 center, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, int tile_size, Direction direction, float velocity, Type type, State state, SpriteMap sprite_map)
	: CActor(center, position, rotation, scale, tile_size, direction, velocity), m_type(type), m_state(state), m_sprite_map(sprite_map) {}

CCharacter::~CCharacter() {}

void CCharacter::SetSpriteReadMode(State state, CSprite::ReadMode read_mode, int play_row, int play_col, int row_num, int col_num)
{
	m_sprite_map[state]->SetReadMode(read_mode, play_row, play_col, row_num, col_num);
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

void CCharacter::Move(D3DXVECTOR3 offset)
{
	m_position += offset;
	m_sprite_map[m_state]->SetPosition(m_position);
	m_sprite_map[m_state]->SetPlayState(CSprite::PS_CYCLE);
	m_sprite_map[m_state]->Update();
}

void CCharacter::Destroy()
{

}

void CCharacter::Draw()
{
	m_sprite_map[m_state]->Draw();
}

GET_SET_FUN_DEFINE(CCharacter::Type, CCharacter, m_type, Type)
GET_SET_FUN_DEFINE(CCharacter::State, CCharacter, m_state, State)
GET_SET_FUN_DEFINE(CCharacter::SpriteMap, CCharacter, m_sprite_map, SpriteMap)
