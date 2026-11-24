#pragma once

#include <Utils.h>
#include <Graphic.h>

class CSprite
{
public:
	enum PlayState
	{
		PS_STOP,
		PS_CYCLE,
		PS_CYCLE_TERMINAL,
		PS_ONCE,
	};

	enum ReadMode
	{
		RM_HORIZONTAL,
		RM_ONE_ROW,
		RM_ONE_COL,
	};

	enum Direction
	{
		D_DOWN,
		D_RIGHT,
		D_UP,
		D_LEFT,
	};

/* 图像 */
GET_SET_FUN_DECLAR(Image*, m_img, Img)
GET_SET_FUN_DECLAR(int, m_row_num, RowNum)
GET_SET_FUN_DECLAR(int, m_col_num, ColNum)

/* 图像变换 */
GET_SET_FUN_DECLAR(D3DXVECTOR3, m_center, Center)
GET_SET_FUN_DECLAR(D3DXVECTOR3, m_position, Position)
GET_SET_FUN_DECLAR(D3DXVECTOR3, m_rotation, Rotation)
GET_SET_FUN_DECLAR(D3DXVECTOR3, m_scale, Scale)
GET_SET_FUN_DECLAR(Direction, m_default_direction, DefaultDirection)

/* 帧 */
GET_SET_FUN_DECLAR(float, m_frame_width, FrameWidth)
GET_SET_FUN_DECLAR(float, m_frame_height, FrameHeight)
GET_SET_FUN_DECLAR(int, m_frame_count, FrameCount)

/* 读取帧 */
GET_SET_FUN_DECLAR(ReadMode, m_read_mode, ReadMode)
GET_SET_FUN_DECLAR(PlayState, m_play_state, PlayState)
GET_SET_FUN_DECLAR(bool, m_is_visible, IsVisible)
GET_SET_FUN_DECLAR(int, m_cur_frame, CurFrame)
GET_SET_FUN_DECLAR(int, m_play_row, PlayRow)
GET_SET_FUN_DECLAR(int, m_play_col, PlayCol)
GET_SET_FUN_DECLAR(unsigned, m_frame_terminal, FrameTerminal)
GET_SET_FUN_DECLAR(unsigned, m_cycle_terminal, CycleTerminal)
GET_SET_FUN_DECLAR(unsigned, m_waited_time, WaitedTime)

public:
	CSprite();

	CSprite(Image* img, int row_num = 1, int col_num = 1,
		D3DXVECTOR3 center = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 rotation = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 scale = D3DXVECTOR3(1, 1, 1), Direction default_direction = D_RIGHT,
		ReadMode read_mode = RM_HORIZONTAL, int play_row = 0, int play_col = 0);

	void Update();

	void Draw();
};
