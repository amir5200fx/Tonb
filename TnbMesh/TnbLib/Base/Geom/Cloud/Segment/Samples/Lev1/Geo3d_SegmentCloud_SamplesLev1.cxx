#include <Geo3d_SegmentCloud_SamplesLev1.hxx>

#include <Global_Macros.hxx>

std::vector<Standard_Real> 
tnbLib::Geo3d_SegmentCloud_SamplesLev1::CalcSamples
(
	const Standard_Real x0,
	const Standard_Real x1
) const
{
	auto centre = MEAN(x0, x1);
	auto p0 = MEAN(x0, centre);
	auto p1 = MEAN(centre, x1);
	std::vector<Standard_Real> samples;
	samples.reserve(3);
	samples.push_back(p0);
	samples.push_back(p1);
	samples.push_back(centre);
	return std::move(samples);
}