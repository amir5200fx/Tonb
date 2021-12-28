#include <Cad_ApprxMetricCriterion_MinMax.hxx>

#include <Geo2d_SamplePoints.hxx>
#include <Cad_Tools.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Metric1.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::Cad_ApprxMetricCriterion_MinMax::Subdivide
(
	const Entity2d_Box & theDomain, 
	const std::shared_ptr<Geo2d_SamplePoints>& theSamples,
	const Handle(Geom_Surface)& theGeometry
) const
{
	Debug_Null_Pointer(theSamples);
	auto samples = theSamples->RetrieveSamples();

	const auto d = theDomain.Diameter();

	const auto& p0 = theDomain.P0();
	const auto& p1 = theDomain.P1();

	Standard_Real minDis = RealLast();
	Standard_Real maxDis = RealFirst();
	for (const auto& s : samples)
	{
		auto[x, y] = s.Components();
		auto xy = std::make_pair(x, y);

		auto[px, py] = Geo_Tools::Interpolate(theDomain, xy);
		auto m = Cad_Tools::CalcMetric(px, py, theGeometry);

		auto dis = Entity2d_Metric1::DistanceSQ(p0, p1, m);

		if (dis < minDis)
		{
			minDis = dis;
		}

		if (dis > maxDis)
		{
			maxDis = dis;
		}
	}
	
	minDis = std::sqrt(minDis);
	maxDis = std::sqrt(maxDis);

	if (std::abs(maxDis - minDis) / maxDis < Tolerance())
	{
		return Standard_False;
	}
	else
	{
		return Standard_True;
	}
}