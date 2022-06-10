#pragma once
#ifndef _Geo_CurveLenMetricPrcsr_Header
#define _Geo_CurveLenMetricPrcsr_Header

#include <Geo_Traits.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	template<class SizeFun, class MetricFun = void>
	class Geo_CurveLenMetricPrcsr
	{

	public:

		typedef typename SizeFun::ptType Point;
		typedef typename MetricFun::metricType metricType;

		typedef Point ptType;
		typedef typename cascadeLib::vec_type_from_point<Point>::vcType vcType;

	private:

		/*Private Data*/

		std::shared_ptr<SizeFun> theSizeFunction_;
		std::shared_ptr<MetricFun> theMetricFunction_;

	public:

		// default constructor [6/5/2022 Amir]

		Geo_CurveLenMetricPrcsr()
		{}

		// constructors [6/5/2022 Amir]


		// public functions and operators [6/5/2022 Amir]

		const std::shared_ptr<SizeFun>& SizeFunction() const
		{
			return theSizeFunction_;
		}

		const std::shared_ptr<MetricFun>& MetricFunction() const
		{
			return theMetricFunction_;
		}

		void SetSizeFunction(const std::shared_ptr<SizeFun>& theFun)
		{
			theSizeFunction_ = theFun;
		}

		void SetMetricFunction(const std::shared_ptr<MetricFun>& theFun)
		{
			theMetricFunction_ = theFun;
		}

		Standard_Real CalcElementSize
		(
			const Point& theCoord
		) const;

		metricType CalcMetric
		(
			const Point& theCoord
		) const;

		Standard_Real Integrand
		(
			const Point& thePoint,
			const Point& theVector
		) const;

		Standard_Real Integrand
		(
			const Point& thePoint,
			const vcType& theVector
		) const;

		Standard_Real IntegrandPerSize
		(
			const Point& thePoint,
			const Point& theVector
		) const;

		Standard_Real IntegrandPerSize
		(
			const Point& thePoint,
			const vcType& theVector
		) const;
	};
}

#include <Geo_CurveLenMetricPrcsrI.hxx>

#endif // !_Geo_CurveLenMetricPrcsr_Header
