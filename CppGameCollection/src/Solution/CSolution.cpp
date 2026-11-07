#include "CSolution.h"

#include <iostream>

#include "src/Utils/Utils.h"

CSolution::CSolution() {}

CSolution::~CSolution() {}

void CSolution::Run()
{
	char* str = fun();
	std::cout << str << std::endl;
	delete[] str;
}

char* fun()
{
	return new char[]("Hello World");
}
