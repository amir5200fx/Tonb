#include <Geo_BoxTools.hxx>

#include <Entity2d_Triangulation.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Geo2d_DelTri.hxx>
#include <Merge2d_Pnt.hxx>

void tnbLib::Geo_BoxTools::GetTriangulation
(
	const std::vector<Entity2d_Box>& theBoxes, 
	Entity2d_Triangulation & theTri
)
{
	std::vector<Pnt2d> pnts;
	pnts.reserve(4 * theBoxes.size());

	for (const auto& x : theBoxes)
	{
		pnts.push_back(x.Corner(Box2d_PickAlgorithm_SW));
		pnts.push_back(x.Corner(Box2d_PickAlgorithm_SE));
		pnts.push_back(x.Corner(Box2d_PickAlgorithm_NE));
		pnts.push_back(x.Corner(Box2d_PickAlgorithm_NW));
	}

	std::vector<Pnt2d> merged;
	{
		Merge2d_Pnt mergeAlg(Triangulation_Merge_Resolution, Triangulation_Merge_Radius);
		mergeAlg.SetCoords(pnts);
		mergeAlg.Perform();

		merged = mergeAlg.CompactPoints();
	}
	
	Geo2d_DelTri triAlg(merged);
	triAlg.Triangulate();

	theTri.Points() = std::move(merged);
	theTri.Connectivity() = std::move(triAlg.Data()->Connectivity());
}