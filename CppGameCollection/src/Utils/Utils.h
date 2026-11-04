#pragma once

#pragma comment(lib, "MSIMG32.LIB")

#include <graphics.h>

/**
 * @brief 透明绘制，并支持放大/缩小
 * @param x
 * @param y
 * @param w
 * @param h
 * @param img
 */
void putimage_alpha_zoom(int x, int y, int w, int h, IMAGE* img);

/**
 * @brief 透明绘制，并支持等比放大/缩小
 * @param x
 * @param y
 * @param scale 
 * @param img
 */
void putimage_alpha_zoom(int x, int y, int scale, IMAGE* img);
