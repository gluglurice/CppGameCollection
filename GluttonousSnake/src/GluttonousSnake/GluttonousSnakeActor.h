#pragma once

#include <string>

#include <graphics.h>

#include "src/Utils/Utils.h"

namespace gluttonous_snake
{
	/* 位置 */
	struct Position
	{
		int x;
		int y;
		Position() {}
		Position(int x, int y) : x(x), y(y) {}

		bool operator<(const Position& other) const
		{
			if (x != other.x)
			{
				return x < other.x;
			}
			return y < other.y;
		}
	};
}
