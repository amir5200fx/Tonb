#include <Geo_BoxTools.hxx>

#include <Entity2d_Triangulation.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Geo2d_DelTri.hxx>
#include <Merge2d_Pnt.hxx>

std::shared_ptr<tnbLib::Entity2d_Triangulation> 
tnbLib::Geo_BoxTools::Triangulate(const Entity2d_Box & b)
{
	const auto& p0 = b.P0();
	const auto p1 = b.Corner(Box2d_PickAlgorithm_SE);
	const auto& p2 = b.P1();
	const auto p3 = b.Corner(Box2d_PickAlgorithm_NW);

	auto tri = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(tri);

	auto& points = tri->Points();
	points.reserve(4);

	points.push_back(p0);
	points.push_back(std::move(p1));
	points.push_back(p2);
	points.push_back(std::move(p3));

	auto& indices = tri->Connectivity();
	indices.reserve(2);

	connectivity::triple i0;
	i0.Value(0) = 1;
	i0.Value(1) = 2;
	i0.Value(2) = 3;

	connectivity::triple i1;
	i1.Value(0) = 3;
	i1.Value(1) = 4;
	i1.Value(2) = 1;

	indices.push_back(std::move(i0));
	indices.push_back(std::move(i1));
	return std::move(tri);
}

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