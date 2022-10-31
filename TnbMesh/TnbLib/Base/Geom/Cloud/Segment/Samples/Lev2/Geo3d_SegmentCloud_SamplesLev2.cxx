#include <Geo3d_SegmentCloud_SamplesLev2.hxx>

#include <Global_Macros.hxx>

std::vector<Standard_Real>
tnbLib::Geo3d_SegmentCloud_SamplesLev2::CalcSamples
(
	const Standard_Real x0,
	const Standard_Real x1
) const
{
	auto centre = MEAN(x0, x1);
	auto p0 = MEAN(x0, centre);
	auto p1 = MEAN(centre, x1);
	auto m0 = MEAN(x0, p0);
	auto m1 = MEAN(p0, centre);
	auto m2 = MEAN(centre, p1);
	auto m3 = MEAN(p1, x1);
	std::vector<Standard_Real> samples;
	samples.reserve(9);
	samples.push_back(x0);
	samples.push_back(m0);
	samples.push_back(p0);
	samples.push_back(m1);
	samples.push_back(centre);
	samples.push_back(m2);
	samples.push_back(p1);
	samples.push_back(m3);
	samples.push_back(x1);
	return std::move(samples);
}