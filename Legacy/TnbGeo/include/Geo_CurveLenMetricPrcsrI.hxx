#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class SizeFun, class MetricFun>
inline Standard_Real
tnbLib::Geo_CurveLenMetricPrcsr<SizeFun, MetricFun>::CalcElementSize
(
	const Point & theCoord
) const
{
	Debug_Null_Pointer(theSizeFunction_);
	return theSizeFunction_->Value(theCoord);
}

template<class SizeFun, class MetricFun>
inline typename tnbLib::Geo_CurveLenMetricPrcsr<SizeFun, MetricFun>::metricType
tnbLib::Geo_CurveLenMetricPrcsr<SizeFun, MetricFun>::CalcMetric
(
	const Point & theCoord
) const
{
	Debug_Null_Pointer(theMetricFunction_);
	auto m = theMetricFunction_->Value(theCoord);
	return std::move(m);
}

template<class SizeFun, class MetricFun>
inline Standard_Real 
tnbLib::Geo_CurveLenMetricPrcsr<SizeFun, MetricFun>::Integrand
(
	const Point & thePoint, 
	const Point & theVector
) const
{
	return std::sqrt(DotProduct(theVector, CalcMetric(thePoint).Multiplied(theVector)));
}

template<class SizeFun, class MetricFun>
inline Standard_Real 
tnbLib::Geo_CurveLenMetricPrcsr<SizeFun, MetricFun>::Integrand
(
	const Point & thePoint, 
	const vcType & theVector
) const
{
	return std::sqrt(theVector.Dot(CalcMetric(thePoint).Multiplied(theVector)));
}

template<class SizeFun, class MetricFun>
inline Standard_Real 
tnbLib::Geo_CurveLenMetricPrcsr<SizeFun, MetricFun>::IntegrandPerSize
(
	const Point & thePoint, 
	const Point & theVector
) const
{
	return std::sqrt(DotProduct(theVector, CalcMetric(thePoint).Multiplied(theVector)))
		/ CalcElementSize(thePoint);
}

template<class SizeFun, class MetricFun>
inline Standard_Real 
tnbLib::Geo_CurveLenMetricPrcsr<SizeFun, MetricFun>::IntegrandPerSize
(
	const Point & thePoint,
	const vcType & theVector
) const
{
	return std::sqrt(theVector.Dot(CalcMetric(thePoint).Multiplied(theVector)))
		/ CalcElementSize(thePoint);
}