#include "CActor.h"

CActor::CActor() {}

CActor::CActor(const Position& position, const std::wstring& img_path)
{
	m_position = position;
	LoadImg(img_path);
}

CActor::~CActor() {}

void CActor::LoadImg(const std::wstring& img_path)
{
	loadimage(&m_img, img_path.c_str());
}

void CActor::Draw(const int scale)
{
	putimage_alpha_zoom(m_position.x, m_position.y, scale, &m_img);
}

GET_SET_FUN_DEFINE(CActor::Position, CActor, m_position, Position)

GET_SET_FUN_DEFINE(IMAGE, CActor, m_img, Img)
