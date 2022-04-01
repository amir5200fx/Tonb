#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
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

}

template<class Point>
inline void tnbLib::Entity_Polygon<Point>::Check
(
	const Entity_Polygon<Point>& thePoly
)
{
	const auto& pts = thePoly.Points();
	if (pts.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< " A polygon must have at least two points." << endl
			<< abort(FatalError);
	}
}