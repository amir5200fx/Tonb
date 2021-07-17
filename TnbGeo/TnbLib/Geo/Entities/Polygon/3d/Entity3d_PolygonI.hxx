#pragma once
namespace tnbLib
{

	template<>
	inline const Pnt3d& Entity3d_Polygon::Coord(const Standard_Integer theIndex) const
	{
		return thePoints_[theIndex];
	}

	template<>
	inline Pnt3d& Entity3d_Polygon::Coord(const Standard_Integer theIndex)
	{
		return thePoints_[theIndex];
	}
}