#include <Geo_Tools.hxx>

#include <Entity2d_Triangle.hxx>
#include <Entity3d_Triangle.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity3d_Chain.hxx>
#include <Entity3d_Triangulation.hxx>

#include <gp_Pln.hxx>

tnbLib::Pnt2d
tnbLib::Geo_Tools::GetIntersectionPoint
(
	const std::shared_ptr<IntersectEntity2d>& entity
)
{
	auto ent = std::dynamic_pointer_cast<PointIntersectEntity2d>(entity);
	if (NOT ent)
	{
		FatalErrorIn(FunctionSIG)
			<< " the intersection type is not point" << endl
			<< abort(FatalError);
	}
	return ent->IntPnt;
}

tnbLib::Entity2d_Segment
tnbLib::Geo_Tools::GetIntersectionSegment
(
	const std::shared_ptr<IntersectEntity2d>& entity
)
{
	auto ent = std::dynamic_pointer_cast<SegmentIntersectEntity2d>(entity);
	if (NOT ent)
	{
		FatalErrorIn(FunctionSIG)
			<< " the intersection type is not segment" << endl
			<< abort(FatalError);
	}
	Entity2d_Segment seg(ent->Segment.P0(), ent->Segment.P1());
	return std::move(seg);
}

tnbLib::Pnt2d 
tnbLib::Geo_Tools::IntersectionTwoLines
(
	const Pnt2d & P0,
	const Dir2d & td0, 
	const Pnt2d & P1, 
	const Dir2d & td1,
	const Standard_Real theTol
)
{
	if (td0.IsParallel(td1, theTol))
	{
		FatalErrorIn(FunctionSIG)
			<< "the two lines are parallel" << endl
			<< abort(FatalError);
	}

	Vec2d t0(td0.XY());
	Vec2d t1(td1.XY());

	const auto dp = P1 - P0;
	const auto denom = t0.Crossed(t1);

	const auto nume = Vec2d(dp.XY()).Crossed(t1);

	const auto alf = nume / denom;

	const auto pt = P0 + alf * Pnt2d(t0.XY());
	return std::move(pt);
}

std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Geo_Tools::RetrieveChain
(
	const Entity2d_Polygon & thePoly
)
{
	auto chain = std::make_shared<Entity2d_Chain>();
	Debug_Null_Pointer(chain);

	chain->Points() = thePoly.Points();
	chain->Connectivity() = dualConnectivityList_Chain(thePoly.NbPoints() - 1);
	
	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Chain>
tnbLib::Geo_Tools::RetrieveChain
(
	const Entity3d_Polygon & thePoly
)
{
	auto chain = std::make_shared<Entity3d_Chain>();
	Debug_Null_Pointer(chain);

	chain->Points() = thePoly.Points();
	chain->Connectivity() = dualConnectivityList_Chain(thePoly.NbPoints() - 1);

	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Geo_Tools::RetrieveChain
(
	const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePoly
)
{
	auto chain = std::make_shared<Entity2d_Chain>();
	Debug_Null_Pointer(chain);

	auto& pts = chain->Points();
	auto& indices = chain->Connectivity();

	Standard_Integer nbPts = 0;
	for (const auto& poly : thePoly)
	{
		Debug_Null_Pointer(poly);

		for (const auto& pt : poly->Points())
		{
			pts.push_back(pt);
		}

		auto l = 
			dualConnectivityList_Chain(poly->NbPoints() - 1);
		for (const auto& x : l)
		{
			auto i0 = x.Value(0) + nbPts;
			auto i1 = x.Value(1) + nbPts;

			connectivity::dual edge;

			edge.Value(0) = i0;
			edge.Value(1) = i1;

			indices.push_back(std::move(edge));
		}

		nbPts += poly->NbPoints();
	}
	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Chain>
tnbLib::Geo_Tools::RetrieveChain
(
	const std::vector<std::shared_ptr<Entity3d_Polygon>>& thePoly
)
{
	auto chain = std::make_shared<Entity3d_Chain>();
	Debug_Null_Pointer(chain);

	auto& pts = chain->Points();
	auto& indices = chain->Connectivity();

	Standard_Integer nbPts = 0;
	for (const auto& poly : thePoly)
	{
		Debug_Null_Pointer(poly);

		for (const auto& pt : poly->Points())
		{
			pts.push_back(pt);
		}

		auto l =
			dualConnectivityList_Chain(poly->NbPoints() - 1);
		for (const auto& x : l)
		{
			auto i0 = x.Value(0) + nbPts;
			auto i1 = x.Value(1) + nbPts;

			connectivity::dual edge;

			edge.Value(0) = i0;
			edge.Value(1) = i1;

			indices.push_back(std::move(edge));
		}

		nbPts += poly->NbPoints();
	}
	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Chain>
tnbLib::Geo_Tools::RetrieveChain
(
	const std::vector<std::shared_ptr<Entity3d_Chain>>& theChains
)
{
	auto chain = std::make_shared<Entity3d_Chain>();
	Debug_Null_Pointer(chain);

	auto& pts = chain->Points();
	auto& indices = chain->Connectivity();

	Standard_Integer nbPts = 0;
	for (const auto& ch : theChains)
	{
		Debug_Null_Pointer(ch);

		for (const auto& pt : ch->Points())
		{
			pts.push_back(pt);
		}

		for (const auto& x : ch->Connectivity())
		{
			auto i0 = x.Value(0) + nbPts;
			auto i1 = x.Value(1) + nbPts;

			connectivity::dual edge;

			edge.Value(0) = i0;
			edge.Value(1) = i1;

			indices.push_back(std::move(edge));
		}

		nbPts += ch->NbPoints();
	}
	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Triangulation> 
tnbLib::Geo_Tools::Triangulation
(
	const Entity3d_Chain & theChain
)
{
	auto tr = std::make_shared<Entity3d_Triangulation>();
	Debug_Null_Pointer(tr);

	auto& pts = tr->Points();
	auto& indices = tr->Connectivity();

	pts = theChain.Points();
	for (const auto& x : theChain.Connectivity())
	{
		auto i0 = x.Value(0);
		auto i1 = x.Value(1);

		connectivity::triple t;
		t.Value(0) = i0;
		t.Value(1) = i1;
		t.Value(2) = i0;

		indices.push_back(std::move(t));
	}
	return std::move(tr);
}

std::shared_ptr<tnbLib::Entity2d_Polygon>
tnbLib::Geo_Tools::GetPolygon(const Entity2d_Triangle & t)
{
	auto poly = std::make_shared<Entity2d_Polygon>();
	auto pnts = poly->Points();
	pnts.reserve(3);

	pnts.push_back(t.P0());
	pnts.push_back(t.P1());
	pnts.push_back(t.P2());

	return std::move(poly);
}

std::shared_ptr<tnbLib::Entity2d_Polygon> 
tnbLib::Geo_Tools::GetPolygon
(
	const Entity_Triangle<const Pnt2d&>& t
)
{
	auto poly = std::make_shared<Entity2d_Polygon>();
	auto pnts = poly->Points();
	pnts.reserve(3);

	pnts.push_back(t.P0());
	pnts.push_back(t.P1());
	pnts.push_back(t.P2());

	return std::move(poly);
}

std::vector<tnbLib::Entity2d_Triangle> 
tnbLib::Geo_Tools::GetTriangles
(
	const Entity2d_Triangulation & mesh
)
{
	std::vector<Entity2d_Triangle> tris;
	tris.reserve(mesh.NbConnectivity());

	const auto& pnts = mesh.Points();
	for (const auto& x : mesh.Connectivity())
	{
		auto v0 = Index_Of(x.Value(0));
		auto v1 = Index_Of(x.Value(1));
		auto v2 = Index_Of(x.Value(2));

		const auto& p0 = pnts[v0];
		const auto& p1 = pnts[v1];
		const auto& p2 = pnts[v2];

		Entity2d_Triangle t(p0, p1, p2);

		tris.push_back(std::move(t));
	}
	return std::move(tris);
}

std::shared_ptr<tnbLib::Entity3d_Triangle>
tnbLib::Geo_Tools::ProjectToPlane
(
	const Entity3d_Triangle & theTri,
	const gp_Pln & thePlane
)
{
	const auto& p0 = theTri.P0();
	const auto& p1 = theTri.P1();
	const auto& p2 = theTri.P2();

	auto prjP0 = ProjectToPlane_cgal(p0, thePlane);
	auto prjP1 = ProjectToPlane_cgal(p1, thePlane);
	auto prjP2 = ProjectToPlane_cgal(p2, thePlane);

	auto t = std::make_shared<Entity3d_Triangle>(std::move(prjP0), std::move(prjP1), std::move(prjP2));
	return std::move(t);
}

size_t 
tnbLib::Geo_Tools::FindSpan
(
	const Standard_Real x, 
	const std::vector<Standard_Real>& theSorted
)
{
#ifdef _DEBUG
	CheckSorted(theSorted, "size_t Geo_Tools::FindSpan(Args...)");
#endif // _DEBUG

	auto high = theSorted.size() - 1;
	if (x IS_EQUAL theSorted[high])
	{
		return high;
	}

	size_t low = 0;
	auto mid = (low + high) / 2;
	while (x < theSorted[mid] OR x >= theSorted[mid + 1])
	{
		if (x < theSorted[mid]) high = mid;
		else low = mid;
		mid = (low + high) / 2;
	}
	return mid;
}

std::tuple<Standard_Real, Standard_Real, Standard_Real, Standard_Real> 
tnbLib::Geo_Tools::GetCoefficients
(
	const gp_Pln & thePlane
)
{
	Standard_Real a, b, c, d;
	thePlane.Coefficients(a, b, c, d);
	auto t = std::make_tuple(a, b, c, d);
	return std::move(t);
}

void tnbLib::Geo_Tools::CheckSorted
(
	const std::vector<Standard_Real>& theSorted,
	const char* theName
)
{
	auto iter = theSorted.begin();
	auto x0 = *iter;

	iter++;
	while (iter NOT_EQUAL theSorted.end())
	{
		if (*iter < x0)
		{
			FatalErrorIn(theName)
				<< "the vector is not sorted!" << endl
				<< abort(FatalError);
		}
		x0 = *iter;
		iter++;
	}
}


#include <Entity2d_PolygonTools.hxx>

void tnbLib::Geo_Tools::MakeTrianglesCCW
(
	const std::shared_ptr<Entity2d_Triangulation>& t
)
{
	const auto& pnts = t->Points();
	auto& indices = t->Connectivity();

	for (auto& x : indices)
	{
		auto& i0 = x.Value(0);
		auto& i1 = x.Value(1);
		auto& i2 = x.Value(2);

		const auto& p0 = pnts[Index_Of(i0)];
		const auto& p1 = pnts[Index_Of(i1)];
		const auto& p2 = pnts[Index_Of(i2)];

		Entity_Triangle<const Pnt2d&> tri(p0, p1, p2);
		if (Entity2d_PolygonTools::GetOrientation(tri) IS_EQUAL Entity2d_PolygonOrientation::cw)
		{
			std::swap(i0, i2);
		}
	}
}