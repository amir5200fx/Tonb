#pragma once
namespace tnbLib
{

	template<class Point>
	void Entity_Polygon<Point>::Reverse()
	{
		const auto iMax = (Standard_Integer)thePoints_.size() - 1;
		forThose(Index, 0, thePoints_.size() / 2 - 1)
		{
			std::swap(thePoints_[Index], thePoints_[iMax - Index]);
		}
	}

	template<class Point>
	void Entity_Polygon<Point>::save(TNB_oARCH_TYPE & ar, const unsigned int version) const
	{
		ar << Points();
		ar << Deflection();
	}

	template<class Point>
	void Entity_Polygon<Point>::load(TNB_iARCH_TYPE & ar, const unsigned int version)
	{
		ar >> Points();
		ar >> Deflection();
	}
}