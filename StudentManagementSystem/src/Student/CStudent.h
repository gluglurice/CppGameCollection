#pragma once

#include <iostream>
#include <Utils/Utils.h>

class CStudent
{
GET_SET_FUN_DECLAR(std::string, m_name, Name)
GET_SET_FUN_DECLAR(int, m_id, Id)
GET_SET_FUN_DECLAR(int, m_class, Class)
GET_SET_FUN_DECLAR(int, m_age, Age)

public:

	CStudent();

	CStudent(std::string name, int id, int class_id, int age);

	~CStudent();

	bool operator<(CStudent& other) const;

	bool operator>(CStudent& other) const;

	bool operator<=(CStudent& other) const;

	bool operator>=(CStudent& other) const;

	friend std::ostream& operator<<(std::ostream& out, const CStudent& student);

	friend std::istream& operator>>(std::istream& in, CStudent& student);
};

std::ostream& operator<<(std::ostream& out, const CStudent& student);

std::istream& operator>>(std::istream& in, CStudent& student);
