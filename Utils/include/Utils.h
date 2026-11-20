#pragma once
#pragma comment(lib, "MSIMG32.LIB")

#include <string>

class IMAGE;

#define GET_SET_FUN_DECLAR(type, member, name) \
protected:\
    type member;\
public:\
    type Get##name();\
    void Set##name(type val);

#define GET_SET_FUN_DEFINE(type, class, member, name) \
type class::Get##name()\
{\
    return member;\
}\
void class::Set##name(type val)\
{\
    member = val;\
}

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
void putimage_alpha_zoom(int x, int y, float scale, IMAGE* img);

/**
 * @brief 
 * @param text 
 * @param encoding 
 * @return 
 */
std::wstring StringToWString(const char* text, std::string encoding = "UTF-8");

/**
 * @brief 
 * @param vk 
 * @return 
 */
bool isKeyDown(int vk);
