#include "Utils.h"

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

void putimage_alpha_zoom(int x, int y, int scale, IMAGE* img)
{
    if (!img) return;

    int srcW = img->getwidth();
    int srcH = img->getheight();

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

    AlphaBlend(
        GetImageHDC(NULL),                  // 目标：当前绘图窗口
        x, y, srcW * scale, srcH * scale,    // 目标位置和尺寸（放大后的尺寸）
        GetImageHDC(img),                     // 源：图片 HDC
        0, 0, srcW, srcH,                           // 源位置和原始尺寸
        blend
    );
}
