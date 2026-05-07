#pragma once
namespace tnbLib
{

	inline Pnt3d operator+(const Pnt3d& thePoint, const Vec3d& theVec)
	{
		Pnt3d pt(thePoint.X() + theVec.X(), thePoint.Y() + theVec.Y(), thePoint.Z() + theVec.Z());
		return std::move(pt);
	}

	inline Pnt3d operator+(const Vec3d& theVec, const Pnt3d& thePoint)
	{
		Pnt3d pt(thePoint.X() + theVec.X(), thePoint.Y() + theVec.Y(), thePoint.Z() + theVec.Z());
		return std::move(pt);
	}

	inline Standard_Real DotProduct(const Vec3d& theV0, const Vec3d& theV1)
	{
		return theV0.Dot(theV1);
	}

	inline Vec3d CrossProduct(const Vec3d& theV0, const Vec3d& theV1)
	{
		auto v = theV0.Crossed(theV1);
		return std::move(v);
	}
}