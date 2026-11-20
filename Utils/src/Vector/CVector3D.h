#pragma once

#include "../Utils/Utils.h"

class CVector3D
{
GET_SET_FUN_DECLAR(float, m_x, X)
GET_SET_FUN_DECLAR(float, m_y, Y)
GET_SET_FUN_DECLAR(float, m_z, Z)

public:
	CVector3D();
	CVector3D(float x, float y, float z);
	~CVector3D();

	float Length() const;
	CVector3D Normalized() const;

	CVector3D operator+(const CVector3D& other) const;
	CVector3D operator-(const CVector3D& other) const;
	CVector3D operator*(float scalar) const;
	CVector3D operator/(float scalar) const;

	CVector3D& operator+=(const CVector3D& other);
	CVector3D& operator-=(const CVector3D& other);
	CVector3D& operator*=(float scalar);
	CVector3D& operator/=(float scalar);

	float Dot(const CVector3D& other) const;
	CVector3D Cross(const CVector3D& other) const;
	float DistanceTo(const CVector3D& other) const;
};
