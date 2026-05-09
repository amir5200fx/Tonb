#pragma once
#include <Global_Macros.hxx>

#include <algorithm>
namespace tnbLib
{
	template<class T>
	inline T Geo_Interval<T>::Length() const
	{
		return x1_ - x0_;
	}

	template<class T>
	inline Standard_Boolean 
		Geo_Interval<T>::IsIntersect
		(
			const Geo_Interval & v
		) const
	{
		if (this->Length() <= v.Length())
		{
			if (INSIDE(x0_, v.X0(), v.X1()))
				return Standard_True;
			if (INSIDE(x1_, v.X0(), v.X1()))
				return Standard_True;
			return Standard_False;
		}
		else
		{
			return v.IsIntersect(*this);
		}		
	}

	template<class T>
	inline Standard_Boolean 
		Geo_Interval<T>::IsNull() const
	{
		return Length() IS_EQUAL 0;
	}

	template<class T>
	inline Geo_Interval<T> 
		Geo_Interval<T>::Intersection
		(
			const Geo_Interval & v
		) const
	{
		if (this->IsIntersect(v))
		{
			const auto x0 = std::max(x0_, v.x0_);
			const auto x1 = std::min(x1_, v.x1_);
			return Geo_Interval(x0, x1);
		}
		return Geo_Interval();
	}
}