#pragma once
#pragma comment(lib, "MSIMG32.LIB")

#include <graphics.h>

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

#define GET_SET_FUN_DEFINE_TEMPLATE(type, class, member, name) \
template<typename T>\
type class<T>::Get##name()\
{\
    return member;\
}\
template<typename T>\
void class<T>::Set##name(type val)\
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
void putimage_alpha_zoom(int x, int y, int scale, IMAGE* img);
