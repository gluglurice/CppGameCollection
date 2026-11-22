#pragma once

#include <Utils.h>
#include <Graphic.h>

class CVector3D : public D3DXVECTOR3
{
public:
	using D3DXVECTOR3::D3DXVECTOR3;

	float Length() const;
	float DistanceTo(CVector3D& other);

	float Dot(CVector3D& other);
	CVector3D Cross(CVector3D& other);
};
