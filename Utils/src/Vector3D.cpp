#include "Vector3D.h"

float CVector3D::Length() const
{
	return D3DXVec3Length(this);
}

float CVector3D::DistanceTo(CVector3D& other)
{
	CVector3D diff = other - *this;
	return D3DXVec3Length(&diff);
}

float CVector3D::Dot(CVector3D& other)
{
	return D3DXVec3Dot(this, &other);
}

CVector3D CVector3D::Cross(CVector3D& other)
{
	return CVector3D(*D3DXVec3Cross(new D3DXVECTOR3(), this, &other));
}
