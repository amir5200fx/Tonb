#include <Geo3d_PatchCloud_EdgeSamplesLev0.hxx>

#include <Pnt2d.hxx>

std::vector<tnbLib::Pnt2d> 
tnbLib::Geo3d_PatchCloud_EdgeSamplesLev0::CalcSamples
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
) const
{
	std::vector<Pnt2d> samples;
	samples.push_back(MEAN(theP0, theP1));
	return std::move(samples);
}