#pragma once
namespace tnbLib
{

	template<>
	inline const Pnt2d& Entity_Polygon<std::pair<Pnt2d, Standard_Real>>::Coord(const Standard_Integer theIndex) const
	{
		return thePoints_[theIndex].first;
	}

	template<>
	inline Pnt2d& Entity_Polygon<std::pair<Pnt2d, Standard_Real>>::Coord(const Standard_Integer theIndex)
	{
		return thePoints_[theIndex].first;
	}
}