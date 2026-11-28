#include "Door.h"

#include "Game.h"

CDoor::CDoor() {}

CDoor::CDoor(CVector3D center, CVector3D position_logic, CVector3D position_render, CVector3D rotation, CVector3D scale, int tile_size, Direction direction, float velocity, State state, CActor::SpritesMap sprites, Type type, bool is_open)
	: CActor(center, position_logic, position_render, rotation, scale, tile_size, direction, velocity, state, sprites), m_type(type), m_is_open(is_open)
{
	UpdateCurSprite();
	m_sprites[m_cur_sprite]->SetIsVisible(true);
	m_sprites[m_cur_sprite]->SetPosition(m_position_render);
}

CDoor::~CDoor() {}

void CDoor::UpdateCurSprite()
{
	m_cur_sprite = static_cast<int>(m_state);
}

void CDoor::UpdateState(State state, Direction direction)
{
	CActor::UpdateState(state, direction);
}

void CDoor::Update()
{
	CActor::Update();
}

void CDoor::Idle()
{
	if (m_sprites[m_cur_sprite]->GetPlayState() != CSprite::PS_STOP)
	{
		m_sprites[m_cur_sprite]->SetPlayState(CSprite::PS_STOP);
	}
}

void CDoor::Open()
{
	if (m_sprites[m_cur_sprite]->GetPlayState() != CSprite::PS_ONCE_STOP)
	{
		m_sprites[m_cur_sprite]->SetPlayState(CSprite::PS_ONCE_STOP);
	}
}

void CDoor::Destroy()
{
	CActor::Destroy();
}

void CDoor::Draw()
{
	CActor::Draw();
}

GET_SET_FUN_DEFINE(CDoor::Type, CDoor, m_type, Type)
GET_SET_FUN_DEFINE(bool, CDoor, m_is_open, IsOpen)
