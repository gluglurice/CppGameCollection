#include "Sprite.h"

CSprite::CSprite() {}

CSprite::CSprite(Image* img, int row_num, int col_num,	D3DXVECTOR3 center, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, Direction direction, ReadMode read_mode, int play_row, int play_col, float frame_terminal, float cycle_terminal)
	: m_img(img), m_row_num(row_num), m_col_num(col_num),	m_center(center), m_position(position), m_rotation(rotation), m_scale(scale), m_direction(direction), m_read_mode(read_mode), m_play_row(play_row), m_play_col(play_col), m_frame_terminal(frame_terminal), m_cycle_terminal(cycle_terminal)
{
	/* 读取帧 */
	m_play_state = PS_STOP;
	m_is_visible = true;
	m_cur_frame = 0;
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
}

CSprite::~CSprite()
{
	if (m_img)
	{
		delete m_img;
		m_img = nullptr;
	}
}

void CSprite::Update()
{
	switch (m_play_state)
	{
	case PS_STOP:
		m_cur_frame = 0;
		break;
	case PS_CYCLE:
		m_waited_time += 1.0f;
		if (m_waited_time >= m_frame_terminal)
		{
			m_cur_frame++;
			if (m_cur_frame >= m_frame_count)
			{
				m_cur_frame = 0;
			}
			m_waited_time = 0.0f;
		}
		break;
	case PS_CYCLE_TERMINAL:
		m_waited_time += 1.0f;

		if (m_waited_time >= m_frame_terminal * m_frame_count + m_cycle_terminal)
		{
			m_waited_time = 0.0f;
		}
		else if (m_waited_time >= m_frame_terminal && m_waited_time < m_frame_terminal * m_frame_count)
		{
			m_cur_frame++;
			if (m_cur_frame >= m_frame_count)
			{
				m_cur_frame = 0;
			}
		}
		break;
	case PS_ONCE:
		m_waited_time += 1.0f;
		if (m_waited_time >= m_frame_terminal)
		{
			m_cur_frame++;
			if (m_cur_frame >= m_frame_count)
			{
				m_cur_frame = 0;
				m_play_state = PS_STOP;
				m_is_visible = false;
			}
			m_waited_time = 0.0f;
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

	D3DXVECTOR2 src_pos;
	D3DXVECTOR2 size(m_frame_width, m_frame_height);
	switch (m_read_mode)
	{
	case RM_HORIZONTAL:
		src_pos = { m_cur_frame % m_col_num * m_frame_width, m_cur_frame / m_col_num * m_frame_height };
		break;
	case RM_ONE_ROW:
		src_pos = { m_cur_frame * m_frame_width, m_play_row * m_frame_height };
		break;
	case RM_ONE_COL:
		src_pos = { m_play_col * m_frame_width, m_cur_frame * m_frame_height };
		break;
	}

	CGraphic::GetInstance()->DrawTex(
		m_img->pTex,
		src_pos,
		size,
		m_position,
		m_center,
		m_rotation,
		m_scale
	);
}

GET_SET_FUN_DEFINE(Image*, CSprite, m_img, Img)
GET_SET_FUN_DEFINE(int, CSprite, m_row_num, RowNum)
GET_SET_FUN_DEFINE(int, CSprite, m_col_num, ColNum)

GET_SET_FUN_DEFINE(D3DXVECTOR3, CSprite, m_center, Center)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CSprite, m_position, Position)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CSprite, m_rotation, Rotation)
GET_SET_FUN_DEFINE(D3DXVECTOR3, CSprite, m_scale, Scale)
GET_SET_FUN_DEFINE(CSprite::Direction, CSprite, m_direction, Direction)

GET_SET_FUN_DEFINE(float, CSprite, m_frame_width, FrameWidth)
GET_SET_FUN_DEFINE(float, CSprite, m_frame_height, FrameHeight)
GET_SET_FUN_DEFINE(int, CSprite, m_frame_count, FrameCount)
GET_SET_FUN_DEFINE(int, CSprite, m_cur_frame, CurFrame)

GET_SET_FUN_DEFINE(CSprite::ReadMode, CSprite, m_read_mode, ReadMode)
GET_SET_FUN_DEFINE(CSprite::PlayState, CSprite, m_play_state, PlayState)
GET_SET_FUN_DEFINE(bool, CSprite, m_is_visible, IsVisible)
GET_SET_FUN_DEFINE(int, CSprite, m_play_row, PlayRow)
GET_SET_FUN_DEFINE(int, CSprite, m_play_col, PlayCol)
GET_SET_FUN_DEFINE(float, CSprite, m_frame_terminal, FrameTerminal)
GET_SET_FUN_DEFINE(float, CSprite, m_cycle_terminal, CycleTerminal)
GET_SET_FUN_DEFINE(float, CSprite, m_waited_time, WaitedTime)
