#include "CStudentManagementSystem.h"

#include <conio.h>

#include "src/Array/CArray.h"
#include "src/Student/CStudent.h"

CStudentManagementSystem::CStudentManagementSystem() {}

CStudentManagementSystem::~CStudentManagementSystem() {}

void CStudentManagementSystem::PrintTips()
{
	std::cout << "\n******************************" << std::endl;
	std::cout << "*键入以下按键进行操作：      *" << std::endl;
	std::cout << "*“1”：添加学生             *" << std::endl;
	std::cout << "*“2”：删除学生             *" << std::endl;
	std::cout << "*“3”：查看所有学生         *" << std::endl;
	std::cout << "*“4”：修改学生信息         *" << std::endl;
	std::cout << "*“5”：保存学生信息到文件   *" << std::endl;
	std::cout << "*“6”：从文件加载学生信息   *" << std::endl;
	std::cout << "*“7”：将学生信息按学号排序 *" << std::endl;
	std::cout << "*“0”：退出系统             *" << std::endl;
	std::cout << "******************************\n" << std::endl;
}

void CStudentManagementSystem::Run()
{
	CArray<CStudent> students(INIT_STU_NUM);

	std::cout << "********************************************" << std::endl;
	std::cout << "*                                          *" << std::endl;
	std::cout << "*          欢迎来到学生管理系统！          *" << std::endl;
	std::cout << "*                                          *" << std::endl;
	std::cout << "********************************************" << std::endl;

	CStudent student;
	std::string filename;

	while (true)
	{
		PrintTips();
		char choice = _getch();
		switch (choice)
		{
		case '1':
			std::cout << "请输入学生信息（姓名 学号 班级 年龄 性别（男：1，女：0））：";
			std::cin >> student;
			students.Insert(students.GetCount(), student);
			std::cout << "学生信息添加成功！" << std::endl;
			break;
		case '2':
			std::cout << "请输入要删除的学生在表中的序号：";
			int index;
			std::cin >> index;
			students.Delete(index);
			std::cout << "学生信息删除成功！" << std::endl;
			break;
		case '3':
			if (students.GetCount() == 0)
			{
				std::cout << "当前没有录入的学生信息！" << std::endl;
				break;
			}
			std::cout << "所有学生信息如下：" << std::endl;
			std::cout << "姓名" << "\t\t"
				<< "学号" << "\t\t"
				<< "班级" << "\t\t"
				<< "年龄" << "\t\t"
				<< "性别" << std::endl;
			students.SelectAll();
			break;
		case '4':
			std::cout << "请输入要修改的学生在表中的序号：";
			std::cin >> index;
			std::cout << "请输入新的学生信息（姓名 学号 班级 年龄 性别（男：1，女：0））：";
			std::cin >> student;
			students.Update(index, student);
			std::cout << "学生信息修改成功！" << std::endl;
			break;
		case '5':
			std::cout << "请输入要保存的文件名：";
			std::cin >> filename;
			students.SaveToFile(filename);
			std::cout << "学生信息保存成功！" << std::endl;
			break;
		case '6':
			std::cout << "请输入要加载的文件名：";
			std::cin >> filename;
			students.LoadFromFile(filename);
			std::cout << "学生信息加载成功！" << std::endl;
			break;
		case '7':
			std::cout << "学生信息按学号排序如下：" << std::endl;
			students.InsertSortAscend();
			students.SelectAll();
			break;
		case '0':
			std::cout << "感谢使用学生管理系统，再见！" << std::endl;
			return;
		}
	}
	_getch();
}
