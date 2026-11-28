#include "Vector3D.h"

float CVector3D::Length() const
{
	return D3DXVec3Length(this);
}

float CVector3D::DistanceTo(const CVector3D& other) const
{
	CVector3D diff = other - *this;
	return D3DXVec3Length(&diff);
}

float CVector3D::Dot(const CVector3D& other) const
{
	return D3DXVec3Dot(this, &other);
}

CVector3D CVector3D::Cross(const CVector3D& other) const
{
	return CVector3D(*D3DXVec3Cross(new D3DXVECTOR3(), this, &other));
}

bool CVector3D::NearlyEqual(const CVector3D& other, float epsilon /*= 1e-5f*/) const
{
	return std::abs(this->x - other.x) <= epsilon
		&& std::abs(this->y - other.y) <= epsilon
		&& std::abs(this->z - other.z) <= epsilon;
}

float CVector3D::AngleTo(const CVector3D& other) const
{
	return acosf(this->Dot(other) / (this->Length() * other.Length()));
}

bool CVector3D::operator <(const CVector3D& other) const
{
	if (x != other.x) return x < other.x;
	if (y != other.y) return y < other.y;
	return z < other.z;
}
