#pragma once
#ifndef _Geo_CurveIntegrand_Header
#define _Geo_CurveIntegrand_Header

#include <Geo_Traits.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>

namespace tnbLib
{

	template<class CurveType, class MetricPrcsrType = void>
	class Geo_CurveIntegrand
	{

		/*Private Data*/

		const CurveType& theCurve_;

		MetricPrcsrType theProcessor_;

	public:

		typedef typename cascadeLib::pt_type_from_curve<typename remove_pointer<CurveType>::type>::ptType Point;
		typedef typename cascadeLib::vec_type_from_point<Point>::vcType Vector;

		Geo_CurveIntegrand
		(
			const CurveType& theCurve,
			const MetricPrcsrType& theProcessor
		)
			: theCurve_(theCurve)
			, theProcessor_(theProcessor)
		{}

		const CurveType& Curve() const
		{
			return theCurve_;
		}

		const MetricPrcsrType& Processor() const
		{
			return theProcessor_;
		}

		Point CalcPoint(const Standard_Real x, Vector& theVec) const;
	};

	template<class CurveType>
	class Geo_CurveIntegrand<CurveType, void>
	{

		/*Private Data*/

		const CurveType& theCurve_;

	public:

		typedef typename cascadeLib::pt_type_from_curve<typename remove_pointer<CurveType>::type>::ptType Point;
		typedef typename cascadeLib::vec_type_from_point<Point>::vcType Vector;

		Geo_CurveIntegrand
		(
			const CurveType& theCurve
		)
			: theCurve_(theCurve)
		{}

		const CurveType& Curve() const
		{
			return theCurve_;
		}

		Point CalcPoint(const Standard_Real x, Vector& theVec) const;
	};
}

#include <Geo_CurveIntegrandI.hxx>

#endif // !_Geo_CurveIntegrand_Header