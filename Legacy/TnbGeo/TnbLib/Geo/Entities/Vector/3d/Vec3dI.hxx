#pragma once
inline void tnbLib::Vec3d::operator-=(const tnbLib::Vec3d& right)
{
	Subtract(right);
}

inline void tnbLib::Vec3d::operator+=(const tnbLib::Vec3d& right)
{
	Add(right);
}
inline void tnbLib::Vec3d::operator*=(const Standard_Real scalar)
{
	Multiply(scalar);
}
inline void tnbLib::Vec3d::operator/=(const Standard_Real scalar)
{
	Divide(scalar);
}
namespace tnbLib
{

	inline Pnt3d operator+(const Pnt3d& thePoint, const Vec3d& theVec)
	{
		return { thePoint.X() + theVec.X(), thePoint.Y() + theVec.Y(), thePoint.Z() + theVec.Z() };
	}
	inline Pnt3d operator-(const Pnt3d& pt, const Vec3d& v)
	{
		return { pt.X() - v.X(), pt.Y() - v.Y(), pt.Z() - v.Z() };
	}

	inline Pnt3d operator+(const Vec3d& theVec, const Pnt3d& thePoint)
	{
		return { thePoint.X() + theVec.X(), thePoint.Y() + theVec.Y(), thePoint.Z() + theVec.Z() };
	}
	inline Vec3d operator*(const Standard_Real scalar, const Vec3d& v)
	{
		return v.operator*(scalar);
	}
	inline Vec3d operator*(const Vec3d& v, const Standard_Real scalar)
	{
		return v.operator*(scalar);
	}
	inline Vec3d operator/(const Vec3d& v, const Standard_Real scalar)
	{
		return v.operator/(scalar);
	}

	inline Standard_Real DotProduct(const Vec3d& theV0, const Vec3d& theV1)
	{
		return theV0.Dot(theV1);
	}

	inline Vec3d CrossProduct(const Vec3d& theV0, const Vec3d& theV1)
	{
		return theV0.Crossed(theV1);
	}
}