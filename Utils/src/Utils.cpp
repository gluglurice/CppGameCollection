#include "Utils.h"

#include <stdexcept>

#include <Windows.h>

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
