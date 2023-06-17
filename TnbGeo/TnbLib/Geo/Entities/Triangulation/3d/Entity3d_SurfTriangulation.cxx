#include <Entity3d_SurfTriangulation.hxx>

std::vector<tnbLib::Pnt3d>
tnbLib::RetrieveCoords(const std::vector<Entity3d_SPnt>& thePs)
{
	std::vector<Pnt3d> coords;
	coords.reserve(thePs.size());
	for (const auto& x : thePs)
	{
		coords.push_back(x.Coord());
	}
	return std::move(coords);
}

std::vector<tnbLib::Pnt2d>
tnbLib::RetrieveParaCoords(const std::vector<Entity3d_SPnt>& thePs)
{
	std::vector<Pnt2d> coords;
	coords.reserve(thePs.size());
	for (const auto& x : thePs)
	{
		coords.push_back(x.Para());
	}
	return std::move(coords);
}