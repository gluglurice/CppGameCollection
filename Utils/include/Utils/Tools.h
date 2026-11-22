#pragma once
#include <iostream>

#include <conio.h>
#include <graphics.h>

using namespace std;

void putimage_alpha(int x, int y, IMAGE* img);//函数声明
					//绘制位置     图片        绘制大小宽高  绘制的图片内的位置    
void putimage_alpha(int x, int y, IMAGE* img, int w, int h, int inX, int inY);

