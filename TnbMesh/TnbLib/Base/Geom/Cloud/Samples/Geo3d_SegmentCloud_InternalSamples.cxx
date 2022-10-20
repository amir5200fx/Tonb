#include <Geo3d_SegmentCloud_InternalSamples.hxx>

#include <Geo3d_SegmentCloud_Samples.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<Standard_Real>
tnbLib::Geo3d_SegmentCloud_InternalSamples::CalcCloud
(
	const std::vector<Standard_Real> & thePoly
) const
{
	std::vector<Standard_Real> coords;

	const auto& pts = thePoly;
	if (Samples())
	{
		const auto& samples = Samples();
		for (size_t i = 1; i < pts.size(); i++)
		{
			auto p0 = pts.at(i - 1);
			auto p1 = pts.at(i);

			auto internals = samples->CalcSamples(p0, p1);
			for (auto& p : internals)
			{
				coords.push_back(std::move(p));
			}
		}
	}

	for (auto p : pts)
	{
		coords.push_back(p);
	}
	return std::move(coords);
}