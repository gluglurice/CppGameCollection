#include "Sprite.h"

CSprite::CSprite() {}

CSprite::CSprite(Image* img, int row_num, int col_num,
	D3DXVECTOR3 center, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale,
	ReadMode read_mode)
	: m_img(img), m_row_num(row_num), m_col_num(col_num),
	m_center(center), m_position(position), m_rotation(rotation), m_scale(scale),
	m_read_mode(read_mode)
{
	/* 读取帧 */
	m_play_state = PS_STOP;
	m_is_visible = true;
	m_frame_terminal = 100;
	m_waited_time = 0;

	/* 帧 */
	m_frame_width = img->width / col_num;
	m_frame_height = img->height / row_num;
	switch (read_mode)
	{
	case RM_HORIZONTAL:
		m_frame_count = row_num * col_num;
		break;
	case RM_ONE_ROW:
		m_frame_count = col_num;
		break;
	case RM_ONE_COL:
		m_frame_count = row_num;
		break;
	}
	m_cur_frame = 0;
}

void CSprite::Update()
{
	switch (m_play_state)
	{
	case PS_STOP:
		m_cur_frame = 0;
		break;
	case PS_CYCLE:
		m_waited_time++;
		if (m_waited_time >= m_frame_terminal)
		{
			m_cur_frame++;
			if (m_cur_frame >= m_frame_count)
			{
				m_cur_frame = 0;
			}
			m_waited_time = 0;
		}
		break;
	case PS_ONCE:
		m_waited_time++;
		if (m_waited_time >= m_frame_terminal)
		{
			m_cur_frame++;
			if (m_cur_frame >= m_frame_count)
			{
				m_cur_frame = 0;
				m_play_state = PS_STOP;
				m_is_visible = false;
			}
			m_waited_time = 0;
		}
		break;
	}
}

void CSprite::Draw()
{
	if (!m_is_visible)
	{
		return;
	}
	switch (m_read_mode)
	{
	case RM_HORIZONTAL:
		CGraphic::GetInstance()->DrawTex(
			m_img->pTex,
			{ m_cur_frame % m_col_num * m_frame_width, m_cur_frame / m_col_num * m_frame_height },
			{ m_frame_width, m_frame_height },
			m_position,
			m_center,
			m_rotation,
			m_scale
		);
		break;
	case RM_ONE_ROW:
		CGraphic::GetInstance()->DrawTex(
			m_img->pTex,
			{ m_cur_frame * m_frame_width, m_cur_row * m_frame_height },
			{ m_frame_width, m_frame_height },
			m_position,
			m_center,
			m_rotation,
			m_scale
		);
		break;
	case RM_ONE_COL:
		CGraphic::GetInstance()->DrawTex(
			m_img->pTex,
			{ m_cur_row * m_frame_width, m_cur_frame * m_frame_height },
			{ m_frame_width, m_frame_height },
			m_position,
			m_center,
			m_rotation,
			m_scale
		);
		break;
	}
}

GET_SET_FUN_DEFINE(Image*, CSprite, m_img, Img)
GET_SET_FUN_DEFINE(int, CSprite, m_row_num, RowNum)
GET_SET_FUN_DEFINE(int, CSprite, m_col_num, ColNum)

GET_SET_FUN_DEFINE(D3DXVECTOR3, CSprite, m_center, Center)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CSprite, m_position, Position)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CSprite, m_rotation, Rotation)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CSprite, m_scale, Scale)

GET_SET_FUN_DEFINE(float, CSprite, m_frame_width, FrameWidth)
GET_SET_FUN_DEFINE(float, CSprite, m_frame_height, FrameHeight)
GET_SET_FUN_DEFINE(int, CSprite, m_frame_count, FrameCount)
GET_SET_FUN_DEFINE(int, CSprite, m_cur_frame, CurFrame)

GET_SET_FUN_DEFINE(CSprite::ReadMode, CSprite, m_read_mode, ReadMode)
GET_SET_FUN_DEFINE(CSprite::PlayState, CSprite, m_play_state, PlayState)
GET_SET_FUN_DEFINE(bool, CSprite, m_is_visible, IsVisible)
GET_SET_FUN_DEFINE(int, CSprite, m_cur_row, CurRow)
GET_SET_FUN_DEFINE(unsigned, CSprite, m_frame_terminal, FrameTerminal)
GET_SET_FUN_DEFINE(unsigned, CSprite, m_waited_time, WaitedTime)
