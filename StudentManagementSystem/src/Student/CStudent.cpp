#include "CStudent.h"

CStudent::CStudent() : m_name(""), m_id(0), m_class(0), m_age(0) {}

CStudent::CStudent(std::string name, int id, int class_id, int age) : m_name(name), m_id(id), m_class(class_id), m_age(age) {}

CStudent::~CStudent() {}

bool CStudent::operator< (CStudent& other) const
{
	return m_id < other.GetId();
}

bool CStudent::operator> (CStudent& other) const
{
	return m_id > other.GetId();
}

bool CStudent::operator<= (CStudent& other) const
{
	return m_id <= other.GetId();
}

bool CStudent::operator>= (CStudent& other) const
{
	return m_id >= other.GetId();
}

std::ostream& operator<<(std::ostream& out, const CStudent& student)
{
	out << student.m_name << " " << student.m_id << " " << student.m_class << " " << student.m_age << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, CStudent& student)
{
	in >> student.m_name >> student.m_id >> student.m_class >> student.m_age;
	return in;
}

GET_SET_FUN_DEFINE(std::string, CStudent, m_name, Name)
GET_SET_FUN_DEFINE(int, CStudent, m_id, Id)
GET_SET_FUN_DEFINE(int, CStudent, m_class, Class)
GET_SET_FUN_DEFINE(int, CStudent, m_age, Age)
