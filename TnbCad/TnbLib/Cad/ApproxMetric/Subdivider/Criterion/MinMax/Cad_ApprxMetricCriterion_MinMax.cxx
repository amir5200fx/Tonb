#include <Cad_ApprxMetricCriterion_MinMax.hxx>

#include <Geo2d_SamplePoints.hxx>
#include <Cad_MetricCalculator.hxx>
#include <Cad_Tools.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Metric1.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::cadLib::ApprxMetricCriterion_MinMax::Subdivide
(
	const Entity2d_Box & theDomain, 
	const std::shared_ptr<Geo2d_SamplePoints>& theSamples,
	const Handle(Geom_Surface)& theGeometry
) const
{
	Debug_Null_Pointer(theSamples);
	Debug_Null_Pointer(MetricCalculator());
	auto samples = theSamples->RetrieveSamples();

	Standard_Real minDet = RealLast();
	Standard_Real maxDet = RealFirst();

	for (const auto& s : samples)
	{
		auto[x, y] = s.Components();
		auto xy = std::make_pair(x, y);

		auto[px, py] = Geo_Tools::Interpolate(theDomain, xy);

		auto m = MetricCalculator()->CalcMetric(px, py, theGeometry);
		//auto m = Cad_Tools::CalcMetric(px, py, theGeometry);
		auto det = m.Determinant();

		if (det < minDet)
		{
			minDet = det;
		}

		if (det > maxDet)
		{
			maxDet = det;
		}
	}

	if (std::abs(maxDet - minDet) / maxDet < Tolerance())
	{
		return Standard_False;
	}
	else
	{
		return Standard_True;
	}
}