#include <Geo3d_SegmentCloud_SamplesLev0.hxx>

std::vector<Standard_Real> 
tnbLib::Geo3d_SegmentCloud_SamplesLev0::CalcSamples
(
	const Standard_Real x0,
	const Standard_Real x1
) const
{
	std::vector<Standard_Real> samples;
	samples.reserve(3);
	samples.push_back(x0);
	samples.push_back(MEAN(x0, x1));
	samples.push_back(x1);
	return std::move(samples);
}