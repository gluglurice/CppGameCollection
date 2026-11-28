#pragma once

#include "Actor.h"

class CCharacter : public CActor
{
public:
	enum Camp
	{
		C_PLAYER,
		C_ENEMY,
		C_COUNT,
	};

	enum Type
	{
		T_LINK,
		T_COUNT,
	};

GET_SET_FUN_DECLAR(Camp, m_camp, Camp)
GET_SET_FUN_DECLAR(Type, m_type, Type)

public:
	CCharacter();

	CCharacter(CVector3D center, CVector3D position_logic, CVector3D position_render, CVector3D rotation, CVector3D scale, int tile_size, Direction direction, float velocity, State state, CActor::SpritesMap sprites, Camp camp, Type type);

	~CCharacter();

	void UpdateCurSprite() override;

	void UpdateState(State state, Direction direction) override;

	void Update() override;

	void DetectCollision(CMap* map, CVector3D position) override;

	void Idle() override;

	void MoveRender(CVector3D offset);

	void MoveLogic(CVector3D offset);

	void Destroy() override;

	void Draw() override;
};
