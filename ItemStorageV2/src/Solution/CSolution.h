#pragma once

#include <string>

class CRole;

class CSolution
{
public:
	static const std::string INI_XML_PATH;
	static const std::string SAVE_XML_PATH;

public:
	CSolution();

	~CSolution();

	void Init();

	void SaveXml(CRole& role);

	void LoadXml(CRole& role);

	void Run();
};
