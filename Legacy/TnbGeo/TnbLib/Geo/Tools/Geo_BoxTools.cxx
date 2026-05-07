#include <Geo_BoxTools.hxx>

#include <Entity2d_Triangulation.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Geo2d_DelTri.hxx>
#include <Geo3d_DelTri_CGAL.hxx>
#include <Geo3d_DelTri_Fade3d.hxx>
#include <Merge2d_Pnt.hxx>
#include <Merge3d_Pnt.hxx>

std::shared_ptr<tnbLib::Entity2d_Box> 
tnbLib::Geo_BoxTools::GeoBox
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	auto x0 = std::min(theP0.X(), theP1.X());
	auto x1 = std::max(theP0.X(), theP1.X());
	auto y0 = std::min(theP0.Y(), theP1.Y());
	auto y1 = std::max(theP0.Y(), theP1.Y());

	Pnt2d p0(x0, y0);
	Pnt2d p1(x1, y1);

	auto b = std::make_shared<Entity2d_Box>(std::move(p0), std::move(p1));
	return std::move(b);
}

std::shared_ptr<tnbLib::Entity2d_Box> 
tnbLib::Geo_BoxTools::GeoBox
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1,
	const Pnt2d & theP2
)
{
	const auto[x0, y0] = theP0.Components();
	const auto[x1, y1] = theP1.Components();
	const auto[x2, y2] = theP2.Components();

	auto xmin = x0;
	auto xmax = x0;
	if (x1 < xmin) xmin = x1;
	if (x2 < xmin) xmin = x2;

	if (x1 > xmax) xmax = x1;
	if (x2 > xmax) xmax = x2;

	auto ymin = y0;
	auto ymax = y0;
	if (y1 < ymin) ymin = y1;
	if (y2 < ymin) ymin = y2;
	
	if (y1 > ymax) ymax = y1;
	if (y2 > ymax) ymax = y2;

	Pnt2d p0(xmin, ymin);
	Pnt2d p1(xmax, ymax);

	auto t = std::make_shared<Entity2d_Box>(std::move(p0), std::move(p1));
	return std::move(t);
}

std::shared_ptr<tnbLib::Entity3d_Box> 
tnbLib::Geo_BoxTools::GetBox
(
	const Pnt3d & theP0, 
	const Pnt3d & theP1
)
{
	const auto[x0, y0, z0] = theP0.Components();
	const auto[x1, y1, z1] = theP1.Components();

	const auto xmin = std::min(x0, x1);
	const auto xmax = std::max(x0, x1);
	
	const auto ymin = std::min(y0, y1);
	const auto ymax = std::max(y0, y1);

	const auto zmin = std::min(z0, z1);
	const auto zmax = std::max(z0, z1);

	Pnt3d p0(xmin, ymin, zmin);
	Pnt3d p1(xmax, ymax, zmax);

	auto t = std::make_shared<Entity3d_Box>(std::move(p0), std::move(p1));
	return std::move(t);
}

std::shared_ptr<tnbLib::Entity3d_Box> 
tnbLib::Geo_BoxTools::GetBox
(
	const Pnt3d & theP0,
	const Pnt3d & theP1,
	const Pnt3d & theP2
)
{
	const auto[x0, y0, z0] = theP0.Components();
	const auto[x1, y1, z1] = theP1.Components();
	const auto[x2, y2, z2] = theP2.Components();

	auto xmin = x0;
	auto xmax = x0;
	if (x1 < xmin) xmin = x1;
	if (x2 < xmin) xmin = x2;

	if (x1 > xmax) xmax = x1;
	if (x2 > xmax) xmax = x2;

	auto ymin = y0;
	auto ymax = y0;
	if (y1 < ymin) ymin = y1;
	if (y2 < ymin) ymin = y2;

	if (y1 > ymax) ymax = y1;
	if (y2 > ymax) ymax = y2;

	auto zmin = z0;
	auto zmax = z0;
	if (z1 < zmin) zmin = z1;
	if (z2 < zmin) zmin = z2;

	if (z1 > zmax) zmax = z1;
	if (z2 > zmax) zmax = z2;

	Pnt3d p0(xmin, ymin, zmin);
	Pnt3d p1(xmax, ymax, zmax);

	auto t = std::make_shared<Entity3d_Box>(std::move(p0), std::move(p1));
	return std::move(t);
}

std::shared_ptr<tnbLib::Entity3d_Box>
tnbLib::Geo_BoxTools::GetBox
(
	const Pnt3d & theP0,
	const Pnt3d & theP1, 
	const Pnt3d & theP2, 
	const Pnt3d & theP3
)
{
	const auto[x0, y0, z0] = theP0.Components();
	const auto[x1, y1, z1] = theP1.Components();
	const auto[x2, y2, z2] = theP2.Components();
	const auto[x3, y3, z3] = theP3.Components();

	auto xmin = x0;
	auto xmax = x0;
	if (x1 < xmin) xmin = x1;
	if (x2 < xmin) xmin = x2;
	if (x3 < xmin) xmin = x3;

	if (x1 > xmax) xmax = x1;
	if (x2 > xmax) xmax = x2;
	if (x3 > xmax) xmax = x3;

	auto ymin = y0;
	auto ymax = y0;
	if (y1 < ymin) ymin = y1;
	if (y2 < ymin) ymin = y2;
	if (y3 < ymin) ymin = y3;

	if (y1 > ymax) ymax = y1;
	if (y2 > ymax) ymax = y2;
	if (y3 > ymax) ymax = y3;

	auto zmin = z0;
	auto zmax = z0;
	if (z1 < zmin) zmin = z1;
	if (z2 < zmin) zmin = z2;
	if (z3 < zmin) zmin = z3;

	if (z1 > zmax) zmax = z1;
	if (z2 > zmax) zmax = z2;
	if (z3 > zmax) zmax = z3;

	Pnt3d p0(xmin, ymin, zmin);
	Pnt3d p1(xmax, ymax, zmax);

	auto t = std::make_shared<Entity3d_Box>(std::move(p0), std::move(p1));
	return std::move(t);
}

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
		pnts.clear();
	}
	
	Geo2d_DelTri triAlg(merged);
	triAlg.Triangulate();

	theTri.Points() = std::move(merged);
	auto& c = triAlg.Data()->Connectivity();
	theTri.Connectivity() = std::move(c);
}

void tnbLib::Geo_BoxTools::GetTriangulation
(
	const std::vector<Entity3d_Box>& theBoxes,
	Entity3d_Tetrahedralization & theTri
)
{
	std::vector<Pnt3d> pnts;
	pnts.reserve(8 * theBoxes.size());

	for (const auto& x : theBoxes)
	{
		pnts.push_back(x.Corner(Box3d_PickAlgorithm_Aft_SW));
		pnts.push_back(x.Corner(Box3d_PickAlgorithm_Aft_SE));
		pnts.push_back(x.Corner(Box3d_PickAlgorithm_Aft_NE));
		pnts.push_back(x.Corner(Box3d_PickAlgorithm_Aft_NW));

		pnts.push_back(x.Corner(Box3d_PickAlgorithm_Fwd_SW));
		pnts.push_back(x.Corner(Box3d_PickAlgorithm_Fwd_SE));
		pnts.push_back(x.Corner(Box3d_PickAlgorithm_Fwd_NE));
		pnts.push_back(x.Corner(Box3d_PickAlgorithm_Fwd_NW));
	}

	std::vector<Pnt3d> merged;
	{
		Merge3d_Pnt mergeAlg(Triangulation_Merge_Resolution, Triangulation_Merge_Radius);
		mergeAlg.SetCoords(pnts);
		mergeAlg.Perform();

		merged = mergeAlg.CompactPoints();
		pnts.clear();
	}

	cgalLib::Geo3d_DelTri triAlg(merged);
	triAlg.Perform();

	theTri.Points() = std::move(merged);

	auto& c = triAlg.Triangulation()->Connectivity();
	theTri.Connectivity() = std::move(c);
}

void tnbLib::Geo_BoxTools::GetTriangulation
(
	const std::vector<std::shared_ptr<Entity3d_Box>>& theBoxes,
	Entity3d_Tetrahedralization & theTri
)
{
	std::vector<Pnt3d> pnts;
	pnts.reserve(8 * theBoxes.size());

	for (const auto& x : theBoxes)
	{
		pnts.push_back(x->Corner(Box3d_PickAlgorithm_Aft_SW));
		pnts.push_back(x->Corner(Box3d_PickAlgorithm_Aft_SE));
		pnts.push_back(x->Corner(Box3d_PickAlgorithm_Aft_NE));
		pnts.push_back(x->Corner(Box3d_PickAlgorithm_Aft_NW));

		pnts.push_back(x->Corner(Box3d_PickAlgorithm_Fwd_SW));
		pnts.push_back(x->Corner(Box3d_PickAlgorithm_Fwd_SE));
		pnts.push_back(x->Corner(Box3d_PickAlgorithm_Fwd_NE));
		pnts.push_back(x->Corner(Box3d_PickAlgorithm_Fwd_NW));
	}

	std::vector<Pnt3d> merged;
	{
		Merge3d_Pnt mergeAlg(Triangulation_Merge_Resolution, Triangulation_Merge_Radius);
		mergeAlg.SetCoords(pnts);
		mergeAlg.Perform();

		merged = mergeAlg.CompactPoints();
		pnts.clear();
	}

	fadeLib::Geo3d_DelTri triAlg(merged);
	triAlg.Perform();

	theTri = *triAlg.Triangulation();
}