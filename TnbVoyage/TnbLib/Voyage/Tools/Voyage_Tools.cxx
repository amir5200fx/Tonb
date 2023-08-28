#include <Voyage_Tools.hxx>

#include <VoyageGeo_VelocityBackground.hxx>
#include <VoyageGeo_Path2.hxx>
#include <Voyage_Edge.hxx>
#include <Voyage_Node.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Cad_GeomSurface.hxx>
#include <Pln_Edge.hxx>
#include <Geo2d_DelTri.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <set>

#include <Geom_Surface.hxx>

std::vector<std::shared_ptr<tnbLib::Voyage_Node>> 
tnbLib::Voyage_Tools::RetrieveNodes(const std::vector<std::shared_ptr<Voyage_Edge>>& theEdges)
{
	static auto cmp = [](const std::shared_ptr<Voyage_Node>& theNode0, const std::shared_ptr<Voyage_Node>& theNode1)
	{
		Debug_Null_Pointer(theNode0);
		Debug_Null_Pointer(theNode1);
		return theNode0->Index() < theNode1->Index();
	};
	std::set<std::shared_ptr<Voyage_Node>, decltype(cmp)> compact(cmp);
	for (const auto& x : theEdges)
	{
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		compact.insert(n0);
		compact.insert(n1);
	}
	std::vector<std::shared_ptr<Voyage_Node>> nodes;
	std::copy(compact.begin(), compact.end(), std::back_inserter(nodes));
	std::sort(nodes.begin(), nodes.end(), cmp);
	return std::move(nodes);
}

std::shared_ptr<tnbLib::Voyage_Node> 
tnbLib::Voyage_Tools::NeighborNode
(
	const std::shared_ptr<Voyage_Node>& theCurrent, 
	const std::shared_ptr<Voyage_Edge>& theEdge
)
{
	if (theEdge->Node0() IS_EQUAL theCurrent)
	{
		return theEdge->Node1();
	}
	if (theEdge->Node1() IS_EQUAL theCurrent)
	{
		return theEdge->Node0();
	}
	FatalErrorIn(FunctionSIG)
		<< "the node doesn't belong to the edge." << endl
		<< abort(FatalError);
	return nullptr;
}

std::shared_ptr<tnbLib::Voyage_Edge> 
tnbLib::Voyage_Tools::RetrieveEdge
(
	const std::shared_ptr<Voyage_Node>& theNode0,
	const std::shared_ptr<Voyage_Node>& theNode1
)
{
	if (theNode1->NbEdges() < theNode0->NbEdges())
	{
		return RetrieveEdge(theNode1, theNode0);
	}
	for (const auto& x : theNode0->Edges())
	{
		auto edge = x.second.lock();
		Debug_Null_Pointer(edge);
		auto neighbor = NeighborNode(theNode0, edge);
		if (neighbor IS_EQUAL theNode1)
		{
			return std::move(edge);
		}
	}
	return nullptr;
}

std::shared_ptr<tnbLib::VoyageGeo_VelocityBackground> 
tnbLib::Voyage_Tools::MakeBackground
(
	const std::vector<Pnt2d>& theCoords,
	const std::vector<Vec2d>& theVecolity,
	const Standard_Real theTol
)
{
	auto mesh = std::make_shared<Geo2d_DelTri>(theCoords);
	Debug_Null_Pointer(mesh);
	mesh->Triangulate();
	Debug_If_Condition_Message(NOT mesh->IsDone(), "the application is not performed.");
	const auto& tris = mesh->Data();

	auto meshData = std::make_shared<GeoMesh2d_Data>();
	Debug_Null_Pointer(meshData);
	meshData->Construct(*tris);

	const auto bMesh = std::make_shared<VoyageGeo_SingleVelocityBackground>();
	Debug_Null_Pointer(bMesh);

	auto domain = Geo_BoxTools::GetBox(theCoords, 0);
	auto d = domain.Diameter();
	domain.Expand(d * theTol);

	bMesh->LoadData(std::move(meshData));

	// initiate the current element [8/1/2022 Amir]
	bMesh->InitiateCurrentElement();
	bMesh->SetBoundingBox(std::move(domain));
	bMesh->Sources().resize(tris->NbPoints());

	size_t k = 0;
	for (auto& x : bMesh->Sources())
	{
		x = theVecolity.at(k++);
	}
	return std::move(bMesh);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::Voyage_Tools::ShortestStraightPath
(
	const Pnt2d& theStart, 
	const Pnt2d& theEnd, 
	const std::shared_ptr<Cad_GeomSurface>& theSurface
)
{
	auto domain = theSurface->ParametricBoundingBox();
	const auto period = domain.P1().X() - domain.P0().X();
	auto minDis = theEnd.Distance(theStart);
	auto [x0, y0] = theStart.Components();
	auto [x1, y1] = theEnd.Components();
	const auto dx0 = x1 - x0;
	const auto dy0 = y1 - y0;

	Pnt2d pb;
	Standard_Boolean tag = Standard_False;
	auto end = theEnd;
	{
		auto x1p = x1 + period;
		auto y1p = y1;
		Pnt2d pt(x1p, y1p);
		auto dis = pt.Distance(theStart);
		if (dis < minDis)
		{
			tag = Standard_True;
			minDis = dis;
			auto t = (domain.P1().X() - x0) / (x1p - x0);
			pb = Pnt2d(domain.P1().X(), y0 + t * (y1 - y0));
		}
	}
	{
		auto x1p = x1 - period;
		auto y1p = y1;
		Pnt2d pt(x1p, y1p);
		auto dis = pt.Distance(theStart);
		if (dis < minDis)
		{
			tag = Standard_True;
			minDis = dis;
			auto t = (domain.P0().X() - x0) / (x1p - x0);
			pb = Pnt2d(domain.P0().X(), y0 + t * (y1 - y0));
		}
	}
	std::vector<Pnt2d> coords;
	if (tag)
	{
		coords.push_back(theStart);
		coords.push_back(std::move(pb));
		coords.push_back(theEnd);
	}
	else
	{
		coords.push_back(theStart);
		coords.push_back(theEnd);
	}
	return std::move(coords);
}

std::shared_ptr<tnbLib::Entity2d_Box> 
tnbLib::Voyage_Tools::CalcBoundingBox
(
	const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePolygons, 
	const Standard_Real theTol
)
{
	if (thePolygons.size())
	{
		FatalErrorIn(FunctionSIG)
			<< "the polygon list is empty." << endl
			<< abort(FatalError);
	}
	auto b = Geo_BoxTools::GetBox(thePolygons.at(0)->Points(), 0);
	for (size_t i = 1; i < thePolygons.size(); i++)
	{
		b = Geo_BoxTools::Union
		(
			b, 
			Geo_BoxTools::GetBox(thePolygons.at(i)->Points(), 0)
		);
	}
	auto t = std::make_shared<Entity2d_Box>(std::move(b));
	return std::move(t);
}

std::vector<std::shared_ptr<tnbLib::Entity2d_Polygon>> 
tnbLib::Voyage_Tools::RetrievePolygons
(
	const VoyageGeo_Path2& thePath
)
{
	const auto& curves = thePath.Curves();
	std::vector<std::shared_ptr<Entity2d_Polygon>> polygons;
	polygons.reserve(curves.size());
	for (const auto& curve : curves)
	{
		Debug_Null_Pointer(curve);
		const auto& mesh = curve->Mesh();
		if (NOT mesh)
		{
			FatalErrorIn(FunctionSIG)
				<< "the edge has no mesh." << endl
				<< abort(FatalError);
		}
		polygons.push_back(mesh);
	}
	return std::move(polygons);
}

Standard_Real 
tnbLib::Voyage_Tools::CalcLength
(
	const Entity2d_Polygon& thePolygon, 
	const Geo2d_MetricPrcsrAnIso& theMetric
)
{
	const auto& points = thePolygon.Points();
	Standard_Real tot_dist = 0;
	for (size_t i = 1; i < points.size(); i++)
	{
		const auto& p0 = points.at(i - 1);
		const auto& p1 = points.at(i);

		auto dist = theMetric.CalcDistance(p0, p1);
		tot_dist += dist;
	}
	return tot_dist;
}

std::vector<Standard_Real> 
tnbLib::Voyage_Tools::CalcParameters
(
	const Entity2d_Polygon& thePolygon,
	const Geo2d_MetricPrcsrAnIso& theMetric,
	Standard_Real& theTotLen
)
{
	const auto& pnts = thePolygon.Points();
	if (pnts.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid polygon has been detected." << endl
			<< abort(FatalError);
	}
	std::vector<Standard_Real> t;
	t.reserve(thePolygon.NbPoints());
	t.at(0) = 0;
	Standard_Real tot_dis = 0.;
	for (size_t i = 1; i < pnts.size(); i++)
	{
		const auto& p0 = pnts.at(i - 1);
		const auto& p1 = pnts.at(i);
		auto dis = theMetric.CalcDistance(p0, p1);
		t.at(i) = dis;
		tot_dis += dis;
	}
	for (auto& x : t)
	{
		x /= tot_dis;
	}
	t.at(t.size() - 1) = 1.0;
	theTotLen = tot_dis;
	return std::move(t);
}

tnbLib::Pnt2d 
tnbLib::Voyage_Tools::ConvertToUV(const Pnt2d& theCoordinate)
{
	auto u = Geo_Tools::DegToRadian(theCoordinate.Y()) + PI;
	auto v = Geo_Tools::DegToRadian(theCoordinate.X());
	if (u < 0.0) u = 0.;
	if (u > 2 * PI) u = 2.0 * PI;
	const auto v0 = -0.5 * PI;
	const auto v1 = 0.5 * PI;
	if (v < v0) v = v0;
	if (v > v1) v = v1;
	Pnt2d uv(u, v);
	return std::move(uv);
}

tnbLib::Pnt2d 
tnbLib::Voyage_Tools::ConvertToVoyageSystem(const Pnt2d& thePt)
{
	auto x = Geo_Tools::RadianToDegree(thePt.Y());
	auto y = Geo_Tools::RadianToDegree(thePt.X() - PI);
	return { x,y };
}

Standard_Real 
tnbLib::Voyage_Tools::KtsToKmh(const Standard_Real x)
{
	return 1.852 * x;
}