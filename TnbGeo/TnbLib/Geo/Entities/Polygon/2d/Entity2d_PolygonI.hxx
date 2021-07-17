#pragma once
namespace tnbLib
{

	template<>
	inline const Pnt2d& Entity2d_Polygon::Coord(const Standard_Integer theIndex) const
	{
		return thePoints_[theIndex];
	}

	template<>
	inline Pnt2d& Entity2d_Polygon::Coord(const Standard_Integer theIndex)
	{
		return thePoints_[theIndex];
	}
}