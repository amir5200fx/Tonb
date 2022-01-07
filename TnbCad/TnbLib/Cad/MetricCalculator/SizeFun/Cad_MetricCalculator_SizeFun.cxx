#include <Cad_MetricCalculator_SizeFun.hxx>

#include <Entity2d_Metric1.hxx>
#include <Cad_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Entity2d_Metric1
tnbLib::cadLib::MetricCalculator_SizeFun::CalcMetric
(
	const Pnt2d & theCoord,
	const Handle(Geom_Surface)& theGeometry
) const
{
	Debug_Null_Pointer(theGeometry);
	Debug_Null_Pointer(SizeFunction);
	auto m = Cad_Tools::CalcMetric(theCoord, theGeometry, SizeFunction);
	return std::move(m);
}

tnbLib::Entity2d_Metric1
tnbLib::cadLib::MetricCalculator_SizeFun::CalcMetric
(
	const Standard_Real u,
	const Standard_Real v,
	const Handle(Geom_Surface)& theGeometry
) const
{
	Debug_Null_Pointer(theGeometry);
	Debug_Null_Pointer(SizeFunction);
	auto m = Cad_Tools::CalcMetric(u, v, theGeometry, SizeFunction);
	return std::move(m);
}