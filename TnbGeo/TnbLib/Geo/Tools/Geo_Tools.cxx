#include <Geo_Tools.hxx>

#include <Geo2d_Graph.hxx>
#include <Geo2d_SegmentGraphEdge.hxx>
#include <Geo2d_GraphNode.hxx>
#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Triangle.hxx>
#include <Entity3d_Triangle.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity3d_Chain.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Global_Tools.hxx>

#include <predicates.h>

#ifdef Handle
#undef Handle
#endif // Handle
#include <gp_Pln.hxx>
#include <gp_Lin2d.hxx>

const Standard_Real tnbLib::Geo_Tools::OnePerSix = 1.0 / 6.0;

Standard_Real
tnbLib::Geo_Tools::MachineEpsilon()
{
	return epsilon;
}

arma::mat 
tnbLib::Geo_Tools::CalcRotationMatrix
(
	const Dir3d & theV1,
	const Dir3d & theV2
)
{
	auto v3 = theV1.Crossed(theV2);
	auto v2 = v3.Crossed(theV1);

	static const Dir3d e1(1, 0, 0);
	static const Dir3d e2(0, 1, 0);
	static const Dir3d e3(0, 0, 1);

	arma::mat R(3, 3);

	R(0, 0) = e1.Dot(theV1);
	R(0, 1) = e1.Dot(v2);
	R(0, 2) = e1.Dot(v3);

	R(1, 0) = e2.Dot(theV1);
	R(1, 1) = e2.Dot(v2);
	R(1, 2) = e2.Dot(v3);

	R(2, 0) = e3.Dot(theV1);
	R(2, 1) = e3.Dot(v2);
	R(2, 2) = e3.Dot(v3);

	return std::move(R);
}

namespace tnbLib
{

	template<class T>
	auto GetVec(const T& pt)
	{
		arma::vec p(3);

		p(0) = pt.X();
		p(1) = pt.Y();
		p(2) = pt.Z();

		return std::move(p);
	}
}

std::tuple<tnbLib::Pnt2d, tnbLib::Pnt2d, tnbLib::Pnt2d, arma::mat>
tnbLib::Geo_Tools::ProjectToPlane
(
	const Pnt3d & theP1,
	const Pnt3d & theP2,
	const Pnt3d & theP3
)
{
	Vec3d v1(theP2, theP1);
	Vec3d v2(theP3, theP1);

	auto R1 = CalcRotationMatrix(v1, v2);
	auto R = arma::inv(R1);

	auto p2 = GetVec<Vec3d>(v1);
	auto p3 = GetVec<Vec3d>(v2);

	p2 = R * p2;
	p3 = R * p3;

	auto pp1 = Pnt2d(0, 0);
	auto pp2 = Pnt2d(p2(0), p2(1));
	auto pp3 = Pnt2d(p3(0), p3(1));

	auto t = std::make_tuple(std::move(pp1), std::move(pp2), std::move(pp3), std::move(R));
	return std::move(t);
}

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

Standard_Real 
tnbLib::Geo_Tools::CalcLength
(
	const Entity2d_Polygon & thePoly
)
{
	const auto& pts = thePoly.Points();
	Standard_Real d = 0;
	for (size_t i = 1; i < pts.size(); i++)
	{
		const auto& p0 = pts[i - 1];
		const auto& p1 = pts[i];

		d += p0.Distance(p1);
	}
	return d;
}

Standard_Real 
tnbLib::Geo_Tools::Oriented_Shewchuk
(
	const Pnt3d & theCoord,
	const Pnt3d & P1,
	const Pnt3d & P2,
	const Pnt3d & P3
)
{
	static Standard_Real pa[3];
	static Standard_Real pb[3];
	static Standard_Real pc[3];
	static Standard_Real pd[3];

	pa[0] = P1.X();
	pa[1] = P1.Y();
	pa[2] = P1.Z();

	pb[0] = P2.X();
	pb[1] = P2.Y();
	pb[2] = P2.Z();

	pc[0] = P3.X();
	pc[1] = P3.Y();
	pc[2] = P3.Z();

	pd[0] = theCoord.X();
	pd[1] = theCoord.Y();
	pd[2] = theCoord.Z();

	return -orient3d(pa, pb, pc, pd);
}

Standard_Real 
tnbLib::Geo_Tools::Oriented_Fast
(
	const Pnt3d & theCoord, 
	const Pnt3d & P1,
	const Pnt3d & P2,
	const Pnt3d & P3
)
{
	static Standard_Real pa[3];
	static Standard_Real pb[3];
	static Standard_Real pc[3];
	static Standard_Real pd[3];

	pa[0] = P1.X();
	pa[1] = P1.Y();
	pa[2] = P1.Z();

	pb[0] = P2.X();
	pb[1] = P2.Y();
	pb[2] = P2.Z();

	pc[0] = P3.X();
	pc[1] = P3.Y();
	pc[2] = P3.Z();

	pd[0] = theCoord.X();
	pd[1] = theCoord.Y();
	pd[2] = theCoord.Z();

	return -orient3dfast(pa, pb, pc, pd);
}

Standard_Boolean
tnbLib::Geo_Tools::IsCcwOrder
(
	const std::vector<Pnt2d>& thePts
)
{
	auto Pts = thePts;

	auto iter = Pts.begin();
	auto xMin = iter->X();
	auto yMin = iter->Y();
	auto xMax = xMin;
	auto yMax = yMin;
	iter++;
	while (iter NOT_EQUAL Pts.end())
	{
		auto x = iter->X();
		auto y = iter->Y();

		if (x > xMax) xMax = x;
		if (y > yMax) yMax = y;
		if (x < xMin) xMin = x;
		if (y < yMin) yMin = y;
		iter++;
	}

	auto dx = xMax - xMin;
	auto dy = yMax - yMin;

	for (auto& p : Pts)
	{
		p.X() -= xMin;
		p.Y() -= yMin;
		p.X() /= dx;
		p.Y() /= dy;
	}

	Standard_Real sum = 0;
	for (size_t i = 1; i < Pts.size() - 1; i++)
	{
		sum += CrossProduct(Pts[i - 1], Pts[i]);
	}
	sum += CrossProduct(Pts[Pts.size() - 1], Pts[0]);
	return sum > 0;
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

std::pair<tnbLib::Pnt2d, Standard_Boolean> 
tnbLib::Geo_Tools::IntersectTwoLines
(
	const Pnt2d & P0,
	const Dir2d & td0,
	const Pnt2d & P1, 
	const Dir2d & td1,
	Standard_Real & gamma0, 
	Standard_Real & gamma1, 
	const Standard_Real tol
)
{
	if (td0.IsParallel(td1, tol))
	{
		auto t = std::make_pair(Pnt2d(0, 0), Standard_False);
		return std::move(t);
	}

	Vec2d t0(td0.XY());
	Vec2d t1(td1.XY());

	const auto dp = P1 - P0;
	const auto denom = t0.Crossed(t1);

	const auto nume0 = Vec2d(dp.XY()).Crossed(t1);
	const auto nume1 = Vec2d(dp.XY()).Crossed(t0);

	gamma0 = nume0 / denom;
	gamma1 = nume1 / denom;

	auto pt = P0 + gamma0 * Pnt2d(t0.XY());
	auto t = std::make_pair(std::move(pt), Standard_True);
	return std::move(t);
}

std::pair<tnbLib::Pnt2d, Standard_Boolean> 
tnbLib::Geo_Tools::IntersectTwoLines
(
	const Pnt2d & P0,
	const Vec2d & t0, 
	const Pnt2d & P1, 
	const Vec2d & t1,
	Standard_Real & gamma0, 
	Standard_Real & gamma1, 
	const Standard_Real tol
)
{
	if (t0.IsParallel(t1, tol))
	{
		auto t = std::make_pair(Pnt2d(0, 0), Standard_False);
		return std::move(t);
	}

	const auto dp = P1 - P0;
	const auto denom = t0.Crossed(t1);

	const auto nume0 = Vec2d(dp.XY()).Crossed(t1);
	const auto nume1 = Vec2d(dp.XY()).Crossed(t0);

	gamma0 = nume0 / denom;
	gamma1 = nume1 / denom;

	auto pt = P0 + gamma0 * Pnt2d(t0.XY());
	auto t = std::make_pair(std::move(pt), Standard_True);
	return std::move(t);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::Geo_Tools::Interpolate
(
	const Entity2d_Box & theBox,
	const std::pair<Standard_Real, Standard_Real>& pt
)
{
	const auto[u0, v0] = theBox.P0().Components();
	const auto[u1, v1] = theBox.P1().Components();

	const auto[s, t] = pt;
	const auto u = u0 + t * (u1 - u0);
	const auto v = v0 + s * (v1 - v0);

	auto paired = std::make_pair(u, v);
	return std::move(paired);
}

tnbLib::Entity_Triangle<tnbLib::Pnt2d> 
tnbLib::Geo_Tools::CalcParametricTriangle
(
	const Entity_Triangle<const Pnt3d&>& theTri3d
)
{
	Dir3d v1((theTri3d.P1() - theTri3d.P0()).XYZ());
	Dir3d v2((theTri3d.P2() - theTri3d.P0()).XYZ());

	auto R = arma::inv(CalcRotationMatrix(v1, v2));

	arma::vec3 Q2, Q3;
	Q2(0) = v1.X();
	Q2(1) = v1.Y();
	Q2(2) = v1.Z();

	Q3(0) = v2.X();
	Q3(1) = v2.Y();
	Q3(2) = v2.Z();

	Q2 = R * Q2;
	Q3 = R * Q3;

	Pnt2d p0(0, 0);
	Pnt2d p1(Q2(0), Q2(1));
	Pnt2d p2(Q3(0), Q3(1));

	Entity_Triangle<Pnt2d> t(std::move(p0), std::move(p1), std::move(p2));
	return std::move(t);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::Geo_Tools::DistributeInDomain
(
	const std::vector<Pnt2d>& thePts, 
	const Entity2d_Box & theDomain
)
{
	const auto[xmin, xmax] = theDomain.Bound(0);
	const auto[ymin, ymax] = theDomain.Bound(1);

	const auto b = Entity2d_Box::BoundingBoxOf(thePts);
	const auto[x0, x1] = b.Bound(0);
	const auto[y0, y1] = b.Bound(1);

	std::vector<Pnt2d> pts;
	pts.reserve(thePts.size());
	for (const auto& x : thePts)
	{
		auto tx = CalcLinearPar(x0, x1, x.X());
		auto ty = CalcLinearPar(y0, y1, x.Y());

		auto xp = LinearInterpolate(xmin, xmax, tx);
		auto yp = LinearInterpolate(ymin, ymax, ty);

		Pnt2d pt(xp, yp);
		pts.push_back(std::move(pt));
	}
	return std::move(pts);
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

std::shared_ptr<tnbLib::Entity2d_Triangulation>
tnbLib::Geo_Tools::Triangulation
(
	const Entity2d_Chain & theChain
)
{
	auto tr = std::make_shared<Entity2d_Triangulation>();
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

tnbLib::Entity_Triangle<const tnbLib::Pnt2d&> 
tnbLib::Geo_Tools::GetTriangle
(
	const Standard_Integer theIndex,
	const Entity2d_Triangulation & theTriangulation
)
{
	const auto& indices = theTriangulation.Connectivity();
	const auto& points = theTriangulation.Points();

	const auto& t = indices[theIndex];

	const auto v0 = Index_Of(t.Value(0));
	const auto v1 = Index_Of(t.Value(1));
	const auto v2 = Index_Of(t.Value(2));

	Entity_Triangle<const Pnt2d&> tri(points[v0], points[v1], points[v2]);
	return std::move(tri);
}

size_t 
tnbLib::Geo_Tools::FindSpan
(
	const Standard_Real x, 
	const std::vector<Standard_Real>& theSorted
)
{
	return Global_Tools::FindSpan(x, theSorted);
}

tnbLib::Entity2d_Line 
tnbLib::Geo_Tools::GetLine(const gp_Lin2d & l)
{
	Entity2d_Line line(Pnt2d(l.Position().Location()), Dir2d(l.Direction()));
	return std::move(line);
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

void tnbLib::Geo_Tools::Reverse(Entity2d_Triangulation & theTri)
{
	auto& Ids = theTri.Connectivity();
	for (auto& x : Ids)
	{
		std::swap(x.Value(0), x.Value(1));
	}
}

void tnbLib::Geo_Tools::Reverse(Entity3d_Triangulation & theTri)
{
	auto& Ids = theTri.Connectivity();
	for (auto& x : Ids)
	{
		std::swap(x.Value(0), x.Value(1));
	}
}