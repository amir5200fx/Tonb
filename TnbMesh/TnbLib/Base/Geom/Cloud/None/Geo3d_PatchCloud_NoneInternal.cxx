#include <Geo3d_PatchCloud_NoneInternal.hxx>

#include <Entity2d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<tnbLib::Pnt2d> 
tnbLib::Geo3d_PatchCloud_NoneInternal::CalcCloud
(
	const Entity2d_Triangulation & theTris
) const
{
	std::vector<Pnt2d> coords;
	coords.reserve(theTris.NbPoints());

	const auto& pts = theTris.Points();
	for (const auto& p : pts)
	{
		coords.push_back(p);
	}
	return std::move(coords);
}