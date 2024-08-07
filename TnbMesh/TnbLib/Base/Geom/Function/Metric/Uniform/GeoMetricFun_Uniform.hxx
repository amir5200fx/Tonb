#pragma once
#ifndef _GeoMetricFun_Uniform_Header
#define _GeoMetricFun_Uniform_Header

#include <Geo_MetricFunction.hxx>
#include <Geo_MetricFunctionTraits.hxx>

namespace tnbLib
{

	template<class Point>
	class GeoMetricFun_Uniform
		: public Geo_MetricFunction<Point>
	{

	public:

		typedef typename metric2_type_from_point<Point>::metricType
			metric2;
		typedef typename metric_type_from_point<Point>::metricType
			metric;

	private:

		/*Private Data*/

		metric theMetric_;


		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Geo_MetricFunction<Point>>(*this);
			ar & theMetric_;
		}

	protected:


		metric& ChangeMetric()
		{
			return theMetric_;
		}

	public:

		// default constructor [12/23/2021 Amir]

		GeoMetricFun_Uniform()
		{}

		// constructors [12/23/2021 Amir]

		GeoMetricFun_Uniform
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Entity_Box<Point>& theBox
		)
			: Geo_MetricFunction<Point>(theIndex, theName, theBox)
		{}

		GeoMetricFun_Uniform
		(
			const metric2& theMetric,
			const Entity_Box<Point>& theBox
		)
			: Geo_MetricFunction<Point>(theBox)
		{
			ChangeMetric() = metric2::ConvertTo1(theMetric);
		}

		GeoMetricFun_Uniform
		(
			const metric& theMetric,
			const Entity_Box<Point>& theBox
		)
			: Geo_MetricFunction<Point>(theBox)
			, theMetric_(theMetric)
		{}

		GeoMetricFun_Uniform
		(
			const Standard_Integer theIndex,
			const word& theName,
			const metric2& theMetric,
			const Entity_Box<Point>& theBox
		)
			: Geo_MetricFunction<Point>(theIndex, theName, theBox)
		{
			ChangeMetric() = metric2::ConvertTo1(theMetric);
		}

		GeoMetricFun_Uniform
		(
			const Standard_Integer theIndex,
			const word& theName,
			const metric& theMetric,
			const Entity_Box<Point>& theBox
		)
			: Geo_MetricFunction<Point>(theBox)
			, theMetric_(theMetric)
		{}


		// public functions and operators [12/23/2021 Amir]

		const metric& Metric() const
		{
			return theMetric_;
		}

		metric Value(const Point& theCoord) const override
		{
			return theMetric_;
		}

		void SetMetric(const metric& theM)
		{
			theMetric_ = theM;
		}

		void SetMetric(metric&& theM)
		{
			theMetric_ = std::move(theM);
		}

	};
}

#endif // !_GeoMetricFun_Uniform_Header