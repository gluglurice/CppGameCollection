#include "Character.h"

#include "Game.h"

CCharacter::CCharacter() {}

CCharacter::CCharacter(CVector3D center, CVector3D position_logic, CVector3D position_render, CVector3D rotation, CVector3D scale, int tile_size, Direction direction, float velocity, State state, CActor::SpritesMap sprites, Camp camp)
	: CActor(center, position_logic, position_render, rotation, scale, tile_size, direction, velocity, state, sprites), m_camp(camp) { }

CCharacter::~CCharacter() {}

void CCharacter::UpdateCurSprite()
{
	CActor::UpdateCurSprite();
}

void CCharacter::UpdateState(State state, Direction direction)
{
	CActor::UpdateState(state, direction);
}

void CCharacter::Idle()
{
	CActor::Idle();
}

void CCharacter::MoveRender(CVector3D offset)
{
	CActor::MoveRender(offset);
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
	CActor::Draw();
}

GET_SET_FUN_DEFINE(CCharacter::Camp, CCharacter, m_camp, Camp)
