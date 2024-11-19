#pragma once
#ifndef _Geo_Interval_Header
#define _Geo_Interval_Header

#include <Global_TypeDef.hxx>

namespace tnbLib
{

	template<class T>
	class Geo_Interval
	{

		/*Private Data*/

		T x0_;
		T x1_;

	public:


		//- default constructor

		Geo_Interval()
			: x0_(0)
			, x1_(0)
		{}


		//- constructors

		Geo_Interval(T x0, T x1)
			: x0_(x0)
			, x1_(x1)
		{}

		//- public functions and operators

		auto X0() const
		{
			return x0_;
		}

		auto& X0()
		{
			return x0_;
		}

		auto X1() const
		{
			return x1_;
		}

		auto& X1()
		{
			return x1_;
		}

		T Length() const;

		Standard_Boolean IsIntersect(const Geo_Interval&) const;
		Standard_Boolean IsNull() const;

		Geo_Interval Intersection(const Geo_Interval&) const;

		void SetX0(T x)
		{
			x0_ = x;
		}

		void SetX1(T x)
		{
			x1_ = x;
		}
	};
}

#include <Geo_IntervalI.hxx>

#endif // !_Geo_Interval_Header
