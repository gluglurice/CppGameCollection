#include "Character.h"

#include "Game.h"
#include "Map.h"

CCharacter::CCharacter() {}

CCharacter::CCharacter(CVector3D center, CVector3D position_logic, CVector3D position_render, CVector3D rotation, CVector3D scale, int tile_size, Direction direction, float velocity, State state, CActor::SpritesMap sprites, Camp camp, Type type)
	: CActor(center, position_logic, position_render, rotation, scale, tile_size, direction, velocity, state, sprites), m_camp(camp), m_type(type) { }

CCharacter::~CCharacter() {}

void CCharacter::UpdateCurSprite()
{
	CActor::UpdateCurSprite();
}

void CCharacter::UpdateState(State state, Direction direction)
{
	CActor::UpdateState(state, direction);
}

void CCharacter::Update()
{
	CActor::Update();
}

void CCharacter::DetectCollision(CMap* map, CVector3D position)
{
	if (!map->IsWalkable(position))
	{
		return;
	}
	this->UpdateState(CCharacter::S_MOVE, this->GetDirection());
	this->SetTargetPositionRender(this->GetPositionRender() + CGame::UNIT_VECS[this->GetDirection()] * CGame::MAP_TILE_SIZE);
}

void CCharacter::Idle()
{
	CActor::Idle();
}

void CCharacter::MoveRender(CVector3D offset)
{
	if (m_sprites[m_cur_sprite]->GetPlayState() != CSprite::PS_CYCLE)
	{
		m_sprites[m_cur_sprite]->SetPlayState(CSprite::PS_CYCLE);
	}
	m_position_render += offset;
	m_sprites[m_cur_sprite]->SetPosition(m_position_render);
}

void CCharacter::MoveLogic(CVector3D offset)
{
	m_position_logic += offset;
}

void CCharacter::Destroy()
{
	CActor::Destroy();
}

void CCharacter::Draw()
{
	CActor::Draw();
}

GET_SET_FUN_DEFINE(CCharacter::Camp, CCharacter, m_camp, Camp)
GET_SET_FUN_DEFINE(CCharacter::Type, CCharacter, m_type, Type)
