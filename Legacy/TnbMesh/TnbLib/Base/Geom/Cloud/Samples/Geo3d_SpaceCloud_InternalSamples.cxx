#include <Geo3d_SpaceCloud_InternalSamples.hxx>

#include <Geo3d_SpaceCloud_TetSamples.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<tnbLib::Pnt3d> 
tnbLib::Geo3d_SpaceCloud_InternalSamples::CalcCloud
(
	const Entity3d_Tetrahedralization & theTets
) const
{
	std::vector<Pnt3d> coords;
	if (TetSamples())
	{
		const auto& samples = TetSamples();
		const auto& pts = theTets.Points();
		for (const auto& ids : theTets.Connectivity())
		{
			auto i0 = Index_Of(ids.Value(0));
			auto i1 = Index_Of(ids.Value(1));
			auto i2 = Index_Of(ids.Value(2));
			auto i3 = Index_Of(ids.Value(3));

			const auto& p0 = pts.at(i0);
			const auto& p1 = pts.at(i1);
			const auto& p2 = pts.at(i2);
			const auto& p3 = pts.at(i3);

			auto internals = samples->CalcSamples(p0, p1, p2, p3);
			for (auto& p : internals)
			{
				coords.push_back(std::move(p));
			}
		}
	}

	const auto& pts = theTets.Points();
	for (const auto& p : pts)
	{
		coords.push_back(p);
	}
	return std::move(coords);
}