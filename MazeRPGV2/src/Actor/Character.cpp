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

	CMap::MapElem elem_obj = map->GetMap()[CMap::L_OBJECT][static_cast<int>(position.y)][static_cast<int>(position.x)];
	CMap::MapElem elem_env_fg = map->GetMap()[CMap::L_ENVIRONMENT_FOREGROUND][static_cast<int>(position.y)][static_cast<int>(position.x)];
	int move_tile_num = 1;

	if (elem_obj == CMap::ME_DOOR_SINGLE_OPEN
		|| elem_obj == CMap::ME_DOOR_DOUBLE_LEFT_OPEN
		|| elem_obj == CMap::ME_DOOR_DOUBLE_RIGHT_OPEN
		|| elem_env_fg == CMap::ME_DOOR_WALL_1)
	{
		this->UpdateState(CCharacter::S_MOVE, this->GetDirection());
		move_tile_num++;
		position += CGame::UNIT_VECS[this->GetDirection()];
		while (map->GetMap()[CMap::L_ENVIRONMENT_FOREGROUND][static_cast<int>(position.y)][static_cast<int>(position.x)] != CMap::ME_EMPTY
			|| map->GetMap()[CMap::L_OBJECT][static_cast<int>(position.y)][static_cast<int>(position.x)] != CMap::ME_EMPTY)
		{
			move_tile_num++;
			position += CGame::UNIT_VECS[this->GetDirection()];
		}
		this->SetTargetPositionRender(this->GetPositionRender() + CGame::UNIT_VECS[this->GetDirection()] * CGame::MAP_TILE_SIZE * move_tile_num);
		this->SetTargetPositionLogic(this->GetPositionLogic() + CGame::UNIT_VECS[this->GetDirection()] * move_tile_num);
	}

	else
	{
		this->UpdateState(CCharacter::S_MOVE, this->GetDirection());
		this->SetTargetPositionRender(this->GetPositionRender() + CGame::UNIT_VECS[this->GetDirection()] * CGame::MAP_TILE_SIZE);
		this->SetTargetPositionLogic(this->GetPositionLogic() + CGame::UNIT_VECS[this->GetDirection()]);
	}
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
