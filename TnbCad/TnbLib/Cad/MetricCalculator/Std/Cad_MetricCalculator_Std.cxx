#include <Cad_MetricCalculator_Std.hxx>

#include <Entity2d_Metric1.hxx>
#include <Cad_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Entity2d_Metric1 
tnbLib::cadLib::MetricCalculator_Std::CalcMetric
(
	const Pnt2d & theCoord,
	const Handle(Geom_Surface)& theGeometry
) const
{
	Debug_Null_Pointer(theGeometry);
	auto m = Cad_Tools::CalcMetric(theCoord, theGeometry);
	return std::move(m);
}

tnbLib::Entity2d_Metric1 
tnbLib::cadLib::MetricCalculator_Std::CalcMetric
(
	const Standard_Real u, 
	const Standard_Real v, 
	const Handle(Geom_Surface)& theGeometry
) const
{
	Debug_Null_Pointer(theGeometry);
	auto m = Cad_Tools::CalcMetric(u, v, theGeometry);
	return std::move(m);
}