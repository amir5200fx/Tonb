#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
namespace tnbLib
{

	template<class Point>
	inline const typename Entity_Polygon<Point>::coord & Entity_Polygon<Point>::FirstPoint() const
	{
		Debug_If_Condition(NOT NbPoints());
		return GetPoint(0);
	}

	template<class Point>
	inline const typename Entity_Polygon<Point>::coord & Entity_Polygon<Point>::LastPoint() const
	{
		Debug_If_Condition(NOT NbPoints());
		return GetPoint(NbPoints() - 1);
	}

	template<class Point>
	inline typename Entity_Polygon<Point>::coord & Entity_Polygon<Point>::FirstPointRef()
	{
		Debug_If_Condition(NOT NbPoints());
		return GetPoint(0);
	}

	template<class Point>
	inline typename Entity_Polygon<Point>::coord & Entity_Polygon<Point>::LastPointRef()
	{
		Debug_If_Condition(NOT NbPoints());
		return GetPoint(NbPoints() - 1);
	}

	template<class Point>
	void Entity_Polygon<Point>::Reverse()
	{
		const auto iMax = static_cast<Standard_Integer>(thePoints_.size()) - 1;
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