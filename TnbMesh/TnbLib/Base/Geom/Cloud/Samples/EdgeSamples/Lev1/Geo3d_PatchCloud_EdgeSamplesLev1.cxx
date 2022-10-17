#include <Geo3d_PatchCloud_EdgeSamplesLev1.hxx>

#include <Geo_Tools.hxx>
#include <Pnt2d.hxx>

std::vector<tnbLib::Pnt2d>
tnbLib::Geo3d_PatchCloud_EdgeSamplesLev1::CalcSamples(const Pnt2d & theP0, const Pnt2d & theP1) const
{
	auto centre = Geo_Tools::CalcCentre(theP0, theP1);
	auto p0 = Geo_Tools::CalcCentre(theP0, centre);
	auto p1 = Geo_Tools::CalcCentre(centre, theP1);
	std::vector<Pnt2d> samples;
	samples.reserve(2);
	samples.push_back(std::move(p0));
	samples.push_back(std::move(p1));
	return std::move(samples);
}