#pragma once

#include <string>

#include <graphics.h>
#include <Utils/Utils.h>

class CActor
{
public:

	struct Position
	{
		int x;
		int y;
	};

GET_SET_FUN_DECLAR(Position, m_position, Position)

GET_SET_FUN_DECLAR(IMAGE, m_img, Img)

public:

	CActor();

	~CActor();

	void LoadImg(const std::wstring& img_path);

	void Draw();
};
