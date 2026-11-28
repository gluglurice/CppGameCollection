#pragma once

#include <Utils.h>
#include <Graphic.h>
#include <Sprite.h>
#include <Vector3D.h>

class CActor
{
public:
	enum Direction
	{
		D_DOWN,
		D_RIGHT,
		D_UP,
		D_LEFT,
		D_COUNT,
	};

	enum State
	{
		S_STILL,
		S_IDLE,
		S_MOVE,
		S_COUNT,
	};

	using SpritesMap = map<int, CSprite*>;

GET_SET_FUN_DECLAR(CVector3D, m_center, Center)
GET_SET_FUN_DECLAR(CVector3D, m_position_logic, PositionLogic)
GET_SET_FUN_DECLAR(CVector3D, m_position_render, PositionRender)
GET_SET_FUN_DECLAR(CVector3D, m_target_position_render, TargetPositionRender)
GET_SET_FUN_DECLAR(CVector3D, m_rotation, Rotation)
GET_SET_FUN_DECLAR(CVector3D, m_scale, Scale)
GET_SET_FUN_DECLAR(int, m_tile_size, TileSize)
GET_SET_FUN_DECLAR(Direction, m_direction, Direction)
GET_SET_FUN_DECLAR(float, m_velocity, Velocity)
GET_SET_FUN_DECLAR(State, m_state, State)
GET_SET_FUN_DECLAR(SpritesMap, m_sprites, Sprites)
GET_SET_FUN_DECLAR(int, m_cur_sprite, CurSprite)

public:
	CActor();

	CActor(CVector3D center, CVector3D position_logic, CVector3D position_render, CVector3D rotation, CVector3D scale, int tile_size, Direction direction, float velocity, State state, SpritesMap sprites);

	~CActor();

	virtual void UpdateCurSprite();

	virtual void UpdateState(State state, Direction direction);

	virtual void Update();

	virtual void Idle();

	virtual void Destroy();

	virtual void Draw();
};
