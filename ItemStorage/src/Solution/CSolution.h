#pragma once

#include <string>

class CRole;

class CSolution
{
public:
	static const std::string DEFAULT_SAVE_FILE;

public:
	CSolution();

	~CSolution();

	void SaveXml(const char* filename, CRole& role);

	void LoadXml(const char* filename, CRole& role);

	void Run();
};
