#include "include/Utils.h"

#include <stdexcept>

#include <Windows.h>
#include <graphics.h>

void putimage_alpha_zoom(int x, int y, int w, int h, IMAGE* img)
{
    if (!img) return;

    int srcW = img->getwidth();
    int srcH = img->getheight();

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

    AlphaBlend(
        GetImageHDC(NULL),       // 目标：当前绘图窗口
        x, y, w, h,                           // 目标位置和尺寸（放大后的尺寸）
        GetImageHDC(img),         // 源：图片 HDC
        0, 0, srcW, srcH,              // 源位置和原始尺寸
        blend
    );
}

void putimage_alpha_zoom(int x, int y, float scale, IMAGE* img)
{
    if (!img) return;

    int srcW = img->getwidth();
    int srcH = img->getheight();

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

    AlphaBlend(
        GetImageHDC(NULL),                  // 目标：当前绘图窗口
        x, y, static_cast<int>(srcW * scale), static_cast<int>(srcH * scale),    // 目标位置和尺寸（放大后的尺寸）
        GetImageHDC(img),                     // 源：图片 HDC
        0, 0, srcW, srcH,                           // 源位置和原始尺寸
        blend
    );
}

std::wstring StringToWString(const char* text, std::string encoding)
{
	if (text == nullptr)
		throw std::invalid_argument("text is null");

	int codePage;

	if (encoding == "UTF-8")
	{
		codePage = CP_UTF8;
	}
	else if (encoding == "ANSI")
	{
		codePage = CP_ACP;
	}
	else
	{
		throw std::invalid_argument("unsupported encoding");
	}

	int size = MultiByteToWideChar(codePage, MB_ERR_INVALID_CHARS, text, -1, nullptr, 0);
	if (size == 0)
	{
		throw std::runtime_error("UTF-8 conversion failed");
	}

	std::wstring result(size, L'\0');
	if (MultiByteToWideChar(codePage, MB_ERR_INVALID_CHARS, text, -1, &result[0], size) == 0)
	{
		throw std::runtime_error("UTF-8 conversion failed");
	}

	result.pop_back(); // 移除转换结果末尾的空字符
	return result;
}

bool isKeyDown(int vk)
{
	return (GetAsyncKeyState(vk) & 0x8000) != 0;
}
