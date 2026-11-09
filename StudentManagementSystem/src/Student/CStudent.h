#pragma once

#include <iostream>
#include <Utils/Utils.h>

class CStudent
{
GET_SET_FUN_DECLAR(std::string, m_name, Name)
GET_SET_FUN_DECLAR(int, m_id, Id)
GET_SET_FUN_DECLAR(int, m_class, Class)
GET_SET_FUN_DECLAR(int, m_age, Age)
GET_SET_FUN_DECLAR(bool, m_is_male, IsMale)

public:

	CStudent();

	CStudent(std::string name, int id, int class_id, int age, bool is_male);

	CStudent(CStudent& other) : m_name(other.m_name), m_id(other.m_id), m_class(other.m_class), m_age(other.m_age), m_is_male(other.m_is_male) {}

	~CStudent();

	void operator=(CStudent& other);

	bool operator<(CStudent& other) const;

	bool operator>(CStudent& other) const;

	bool operator<=(CStudent& other) const;

	bool operator>=(CStudent& other) const;

	friend std::ostream& operator<<(std::ostream& out, const CStudent& student);

	friend std::istream& operator>>(std::istream& in, CStudent& student);
};

std::ostream& operator<<(std::ostream& out, const CStudent& student);

std::istream& operator>>(std::istream& in, CStudent& student);
