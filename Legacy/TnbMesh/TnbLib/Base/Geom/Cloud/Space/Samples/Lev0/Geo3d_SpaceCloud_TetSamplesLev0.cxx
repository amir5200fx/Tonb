#include <Geo3d_SpaceCloud_TetSamplesLev0.hxx>

#include <Geo_Tools.hxx>

std::vector<tnbLib::Pnt3d>
tnbLib::Geo3d_SpaceCloud_TetSamplesLev0::CalcSamples
(
	const Pnt3d & theP0,
	const Pnt3d & theP1,
	const Pnt3d & theP2, 
	const Pnt3d & theP3
) const
{
	std::vector<Pnt3d> samples;
	samples.reserve(5);

	samples.push_back(theP0);
	samples.push_back(theP1);
	samples.push_back(theP2);
	samples.push_back(theP3);
	auto centre = Geo_Tools::CalcCentre(theP0, theP1, theP2, theP3);
	samples.push_back(std::move(centre));
	return std::move(samples);
}