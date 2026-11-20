#include "CVector3D.h"

#include <cmath>

CVector3D::CVector3D() {}

CVector3D::CVector3D(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}

CVector3D::~CVector3D() {}

float CVector3D::Length() const
{
	return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

CVector3D CVector3D::Normalized() const
{
	float len = Length();
	return CVector3D(m_x / len, m_y / len, m_z / len);
}

CVector3D CVector3D::operator+(const CVector3D& other) const
{
	return CVector3D(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

CVector3D CVector3D::operator-(const CVector3D& other) const
{
	return CVector3D(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

CVector3D CVector3D::operator*(float scalar) const
{
	return CVector3D(m_x * scalar, m_y * scalar, m_z * scalar);
}

CVector3D CVector3D::operator/(float scalar) const
{
	return CVector3D(m_x / scalar, m_y / scalar, m_z / scalar);
}

CVector3D& CVector3D::operator+=(const CVector3D& other)
{
	m_x += other.m_x;
	m_y += other.m_y;
	m_z += other.m_z;
	return *this;
}

CVector3D& CVector3D::operator-=(const CVector3D& other)
{
	m_x -= other.m_x;
	m_y -= other.m_y;
	m_z -= other.m_z;
	return *this;
}

CVector3D& CVector3D::operator*=(float scalar)
{
	m_x *= scalar;
	m_y *= scalar;
	m_z *= scalar;
	return *this;
}

CVector3D& CVector3D::operator/=(float scalar)
{
	m_x /= scalar;
	m_y /= scalar;
	m_z /= scalar;
	return *this;
}

float CVector3D::Dot(const CVector3D& other) const
{
	return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

CVector3D CVector3D::Cross(const CVector3D& other) const
{
	return CVector3D(m_y * other.m_z - m_z * other.m_y, m_z * other.m_x - m_x * other.m_z, m_x * other.m_y - m_y * other.m_x);
}

float CVector3D::DistanceTo(const CVector3D& other) const
{
	return std::sqrt((m_x - other.m_x) * (m_x - other.m_x) + (m_y - other.m_y) * (m_y - other.m_y) + (m_z - other.m_z) * (m_z - other.m_z));
}

GET_SET_FUN_DEFINE(float, CVector3D, m_x, X)
GET_SET_FUN_DEFINE(float, CVector3D, m_y, Y)
GET_SET_FUN_DEFINE(float, CVector3D, m_z, Z)
