#include "Character.h"

#include "Game.h"

CCharacter::CCharacter() {}

CCharacter::CCharacter(CVector3D center, CVector3D position_logic, CVector3D position_render, CVector3D rotation, CVector3D scale, int tile_size, Direction direction, float velocity, Type type, State state, vector<CSprite*> sprites)
	: CActor(center, position_logic, position_render, rotation, scale, tile_size, direction, velocity), m_type(type), m_state(state), m_sprites(sprites) { }

CCharacter::~CCharacter() {}

void CCharacter::UpdateState(State state, Direction direction)
{
	int old_sprite_index = static_cast<int>(m_state) * static_cast<int>(CActor::Direction::D_COUNT) + static_cast<int>(m_direction);
	int new_sprite_index = static_cast<int>(state) * static_cast<int>(CActor::Direction::D_COUNT) + static_cast<int>(direction);
	m_sprites[old_sprite_index]->SetIsVisible(false);
	m_state = state;
	m_direction = direction;
	m_sprites[new_sprite_index]->SetIsVisible(true);
	m_sprites[new_sprite_index]->SetPosition(m_position_render);
}

void CCharacter::Idle()
{
	int sprite_index = static_cast<int>(m_state) * static_cast<int>(CActor::Direction::D_COUNT) + static_cast<int>(m_direction);
	m_sprites[sprite_index]->SetPlayState(CSprite::PS_CYCLE_TERMINAL);
	m_sprites[sprite_index]->Update(CGame::DELTA_TIME);
}

void CCharacter::MoveRender(CVector3D offset)
{
	CActor::MoveRender(offset);
	int sprite_index = static_cast<int>(m_state) * static_cast<int>(CActor::Direction::D_COUNT) + static_cast<int>(m_direction);
	m_sprites[sprite_index]->SetPlayState(CSprite::PS_CYCLE);
	m_sprites[sprite_index]->SetPosition(m_position_render);
	m_sprites[sprite_index]->Update(CGame::DELTA_TIME);
}

void CCharacter::MoveLogic(CVector3D offset)
{
	CActor::MoveLogic(offset);
}

void CCharacter::Destroy()
{
	CActor::Destroy();
}

void CCharacter::Draw()
{
	int sprite_index = static_cast<int>(m_state) * static_cast<int>(CActor::Direction::D_COUNT) + static_cast<int>(m_direction);
	m_sprites[sprite_index]->Draw();
}

GET_SET_FUN_DEFINE(CCharacter::Type, CCharacter, m_type, Type)
GET_SET_FUN_DEFINE(CCharacter::State, CCharacter, m_state, State)
GET_SET_FUN_DEFINE(vector<CSprite*>, CCharacter, m_sprites, Sprites)
