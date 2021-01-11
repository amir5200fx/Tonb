#pragma once
#ifndef _Geo_MetricPrcsr_Header
#define _Geo_MetricPrcsr_Header

#include <Geo_MetricPrcsr_Base.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>

namespace tnbLib
{

	template<class SizeFun, class MetricFun = void>
	class Geo_MetricPrcsr
		: public Geo_MetricPrcsr_Base<MetricFun>
	{

	public:

		typedef typename SizeFun::ptType Point;
		typedef typename MetricFun::metricType metricType;

		mutable metricType currentMetric;

	private:

		/*Private Data*/

		std::shared_ptr<SizeFun> theSizeFunction_;
		std::shared_ptr<MetricFun> theMetricFunction_;

	public:

		typedef Geo_MetricPrcsr_Base<MetricFun> base;
		typedef typename Geo_MetricPrcsr_Base<MetricFun>::info info;

		typedef Point ptType;
		typedef typename cascadeLib::vec_type_from_point<Point>::vcType vcType;

		Geo_MetricPrcsr(const std::shared_ptr<info>& theInfo)
			: Geo_MetricPrcsr_Base<MetricFun>(theInfo)
		{}

		Geo_MetricPrcsr
		(
			const std::shared_ptr<SizeFun>& theSizeFunction,
			const std::shared_ptr<MetricFun>& theMetricFunction,
			const std::shared_ptr<info>& theInfo
		)
			: Geo_MetricPrcsr_Base<MetricFun>(theInfo)
			, theSizeFunction_(theSizeFunction)
			, theMetricFunction_(theMetricFunction)
		{}

		Geo_MetricPrcsr
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SizeFun>& theSizeFunction,
			const std::shared_ptr<MetricFun>& theMetricFunction,
			const std::shared_ptr<info>& theInfo
		)
			: Geo_MetricPrcsr_Base<MetricFun>(theIndex, theName, theInfo)
			, theSizeFunction_(theSizeFunction)
			, theMetricFunction_(theMetricFunction)
		{}

		const Entity_Box<Point>& BoundingBox() const
		{
			Debug_Null_Pointer(SizeFunction());
			return SizeFunction()->BoundingBox();
		}

		const std::shared_ptr<SizeFun>& SizeFunction() const
		{
			return theSizeFunction_;
		}

		const std::shared_ptr<MetricFun>& MetricFunction() const
		{
			return theMetricFunction_;
		}

		Point CalcCentre
		(
			const Point& theP0,
			const Point& theP1
		) const;

		Standard_Real CalcElementSize
		(
			const Point& theCoord
		) const;

		metricType CalcMetric
		(
			const Point& theCoord
		) const;

		metricType CalcEffectiveMetric
		(
			const Point& theP0,
			const Point& theP1
		) const;

		Standard_Real CalcDistance
		(
			const Point& theP0,
			const Point& theP1
		) const;

		Standard_Real CalcSquareDistance
		(
			const Point& theP0,
			const Point& theP1
		) const;

		Standard_Real CalcUnitDistance
		(
			const Point& theP0,
			const Point& theP1
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


	template<class SizeFun>
	class Geo_MetricPrcsr<SizeFun, void>
		: public Geo_MetricPrcsr_Base<void>
	{

	public:

		typedef typename SizeFun::ptType Point;

	private:

		/*Private Data*/

		std::shared_ptr<SizeFun> theSizeFunction_;

	public:

		typedef Geo_MetricPrcsr_Base<void> base;
		typedef typename Geo_MetricPrcsr_Base<void>::info info;

		typedef Point ptType;
		typedef typename cascadeLib::vec_type_from_point<Point>::vcType vcType;

		Geo_MetricPrcsr(const std::shared_ptr<info>& theInfo)
			: Geo_MetricPrcsr_Base<void>(theInfo)
		{}

		Geo_MetricPrcsr
		(
			const std::shared_ptr<SizeFun>& theSizeFunction,
			const std::shared_ptr<info>& theInfo
		)
			: Geo_MetricPrcsr_Base<void>(theInfo)
			, theSizeFunction_(theSizeFunction)
		{}

		Geo_MetricPrcsr
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SizeFun>& theSizeFunction,
			const std::shared_ptr<info>& theInfo
		)
			: Geo_MetricPrcsr_Base<void>(theIndex, theName, theInfo)
			, theSizeFunction_(theSizeFunction)
		{}

		const Entity_Box<Point>& BoundingBox() const
		{
			Debug_Null_Pointer(SizeFunction());
			return SizeFunction()->BoundingBox();
		}

		const std::shared_ptr<SizeFun>& SizeFunction() const
		{
			return theSizeFunction_;
		}

		Point CalcCentre
		(
			const Point& theP0,
			const Point& theP1
		) const;

		Standard_Real CalcElementSize
		(
			const Point& theCoord
		) const;

		Standard_Real CalcDistance
		(
			const Point& theP0,
			const Point& theP1
		) const;

		Standard_Real CalcSquareDistance
		(
			const Point& theP0,
			const Point& theP1
		) const;

		Standard_Real CalcUnitDistance
		(
			const Point& theP0,
			const Point& theP1
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

#endif // !_Geo_MetricPrcsr_Header
