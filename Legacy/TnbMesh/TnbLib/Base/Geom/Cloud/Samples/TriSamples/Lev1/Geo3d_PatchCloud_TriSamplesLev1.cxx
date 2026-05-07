#include <Geo3d_PatchCloud_TriSamplesLev1.hxx>

#include <Geo_Tools.hxx>
#include <Pnt2d.hxx>

std::vector<tnbLib::Pnt2d> 
tnbLib::Geo3d_PatchCloud_TriSamplesLev1::CalcSamples
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1,
	const Pnt2d & theP2
) const
{
	auto centre = Geo_Tools::CalcCentre(theP0, theP1, theP2);
	auto p0 = Geo_Tools::CalcCentre(centre, theP0, theP1);
	auto p1 = Geo_Tools::CalcCentre(centre, theP1, theP2);
	auto p2 = Geo_Tools::CalcCentre(centre, theP2, theP0);
	auto pm0 = Geo_Tools::CalcCentre(centre, theP0);
	auto pm1 = Geo_Tools::CalcCentre(centre, theP1);
	auto pm2 = Geo_Tools::CalcCentre(centre, theP2);

	std::vector<Pnt2d> samples;
	samples.reserve(7);
	samples.push_back(std::move(p0));
	samples.push_back(std::move(p1));
	samples.push_back(std::move(p2));
	samples.push_back(std::move(centre));
	samples.push_back(std::move(pm0));
	samples.push_back(std::move(pm1));
	samples.push_back(std::move(pm2));

	return std::move(samples);
}