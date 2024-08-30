#pragma once
namespace tnbLib
{

	template<>
	inline const Pnt3d& Entity_Polygon<std::pair<Pnt3d, Standard_Real>>::Coord(const Standard_Integer theIndex) const
	{
		return thePoints_.at(theIndex).first;
	}

	template<>
	inline Pnt3d& Entity_Polygon<std::pair<Pnt3d, Standard_Real>>::Coord(const Standard_Integer theIndex)
	{
		return thePoints_.at(theIndex).first;
	}
}