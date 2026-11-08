#include "CActor.h"

CActor::CActor() {}

CActor::~CActor() {}

void CActor::LoadImg(const std::wstring& img_path)
{
	loadimage(&m_img, img_path.c_str());
}

void CActor::Draw()
{
	putimage_alpha_zoom(m_position.x, m_position.y, 1, &m_img);
}

GET_SET_FUN_DEFINE(CActor::Position, CActor, m_position, Position)

GET_SET_FUN_DEFINE(IMAGE, CActor, m_img, Img)
