#pragma once
#include <Global_Macros.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
inline tnbLib::Pnt2d
tnbLib::Geo_MetricPrcsr<tnbLib::GeoSizeFun2d_Uniform, void>::CalcCentre
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
) const
{
	auto c = MEAN(theP0, theP1);
	return std::move(c);
}

inline Standard_Real 
tnbLib::Geo_MetricPrcsr<tnbLib::GeoSizeFun2d_Uniform, void>::CalcElementSize
(
	const Pnt2d & theCoord
) const
{
	Debug_Null_Pointer(theSizeFunction_);
	return theSizeFunction_->Value(theCoord);
}

inline Standard_Real 
tnbLib::Geo_MetricPrcsr<tnbLib::GeoSizeFun2d_Uniform, void>::CalcDistance
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
) const
{
	return theP0.Distance(theP1);
}

inline Standard_Real 
tnbLib::Geo_MetricPrcsr<tnbLib::GeoSizeFun2d_Uniform, void>::CalcSquareDistance
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1
) const
{
	return theP0.SquareDistance(theP1);
}

inline Standard_Real 
tnbLib::Geo_MetricPrcsr<tnbLib::GeoSizeFun2d_Uniform, void>::CalcUnitDistance
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1
) const
{
	return CalcDistance(theP0, theP1) / CalcElementSize(theP0);
}

inline Standard_Real 
tnbLib::Geo_MetricPrcsr<tnbLib::GeoSizeFun2d_Uniform, void>::Integrand
(
	const Pnt2d & thePoint,
	const Pnt2d & theVector
) const
{
	return sqrt(DotProduct(theVector, theVector));
}

inline Standard_Real 
tnbLib::Geo_MetricPrcsr<tnbLib::GeoSizeFun2d_Uniform, void>::Integrand
(
	const Pnt2d & thePoint, 
	const Vec2d & theVector
) const
{
	return sqrt(theVector.Dot(theVector));
}

inline Standard_Real 
tnbLib::Geo_MetricPrcsr<tnbLib::GeoSizeFun2d_Uniform, void>::IntegrandPerSize
(
	const Pnt2d & thePoint,
	const Pnt2d & theVector
) const
{
	return ((Standard_Real)1.0 / CalcElementSize(thePoint)) * sqrt(DotProduct(theVector, theVector));
}

inline Standard_Real 
tnbLib::Geo_MetricPrcsr<tnbLib::GeoSizeFun2d_Uniform, void>::IntegrandPerSize
(
	const Pnt2d & thePoint,
	const Vec2d & theVector
) const
{
	return ((Standard_Real)1.0 / CalcElementSize(thePoint)) * sqrt(theVector.Dot(theVector));
}