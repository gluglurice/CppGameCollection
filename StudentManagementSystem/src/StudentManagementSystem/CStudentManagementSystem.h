#pragma once

#include <iostream>

class CStudentManagementSystem
{
public:
	static constexpr int INIT_STU_NUM = 10;

public:
	CStudentManagementSystem();

	~CStudentManagementSystem();

	void PrintTips();

	void Run();
};
