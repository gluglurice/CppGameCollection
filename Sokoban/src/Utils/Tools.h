#pragma once
#include <graphics.h>
#include <iostream>
#include <conio.h>
using namespace std;

//使用透明图片绘制的静态库
#pragma comment(lib,"lib/ALPHA.lib")

void putimage_alpha(int x, int y, IMAGE* img);//函数声明
					//绘制位置     图片        绘制大小宽高  绘制的图片内的位置    
void putimage_alpha(int x, int y, IMAGE* img, int w, int h, int inX, int inY);

