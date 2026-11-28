#pragma once

#include <Utils.h>
#include <Graphic.h>

class CVector3D : public D3DXVECTOR3
{
public:
	using D3DXVECTOR3::D3DXVECTOR3;

	float Length() const;
	float DistanceTo(const CVector3D& other) const;

	float Dot(const CVector3D& other) const;
	CVector3D Cross(const CVector3D& other) const;

	bool NearlyEqual(const CVector3D& other, float epsilon = 1e-5f) const;

	float AngleTo(const CVector3D& other) const;

	bool operator <(const CVector3D& other) const;
};
