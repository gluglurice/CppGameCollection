#include "CStudent.h"

CStudent::CStudent() : m_name(""), m_id(0), m_class(0), m_age(0), m_is_male(false) {}

CStudent::CStudent(std::string name, int id, int class_id, int age, bool is_male) : m_name(name), m_id(id), m_class(class_id), m_age(age), m_is_male(is_male) {}

CStudent::~CStudent() {}

void CStudent::operator=(CStudent& other)
{
	m_name = other.m_name;
	m_id = other.m_id;
	m_class = other.m_class;
	m_age = other.m_age;
	m_is_male = other.m_is_male;
}

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
	out << student.m_name << "\t\t"
		<< student.m_id << "\t\t"
		<< student.m_class << "\t\t"
		<< student.m_age << "\t\t"
		<< (student.m_is_male ? "男" : "女");
	return out;
}

std::istream& operator>>(std::istream& in, CStudent& student)
{
	std::string is_male;
	in >> student.m_name >> student.m_id >> student.m_class >> student.m_age >> is_male;
	student.m_is_male = (is_male == "男" ? true : false);
	return in;
}

GET_SET_FUN_DEFINE(std::string, CStudent, m_name, Name)
GET_SET_FUN_DEFINE(int, CStudent, m_id, Id)
GET_SET_FUN_DEFINE(int, CStudent, m_class, Class)
GET_SET_FUN_DEFINE(int, CStudent, m_age, Age)
GET_SET_FUN_DEFINE(bool, CStudent, m_is_male, IsMale)
