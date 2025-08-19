#pragma once
namespace tnbLib
{

	inline Pnt2d operator+(const Pnt2d& thePoint, const Vec2d& theVec)
	{
		Pnt2d pt(thePoint.X() + theVec.X(), thePoint.Y() + theVec.Y());
		return std::move(pt);
	}

	inline Pnt2d operator+(const Vec2d& theVec, const Pnt2d& thePoint)
	{
		Pnt2d pt(thePoint.X() + theVec.X(), thePoint.Y() + theVec.Y());
		return std::move(pt);
	}

	inline Standard_Real DotProduct(const Vec2d& theV0, const Vec2d& theV1)
	{
		return theV0.Dot(theV1);
	}

	inline Standard_Real CrossProduct(const Vec2d& theV0, const Vec2d& theV1)
	{
		return theV0.Crossed(theV1);
	}
}