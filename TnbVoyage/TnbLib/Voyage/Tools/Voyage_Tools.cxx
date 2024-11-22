#include <Voyage_Tools.hxx>

#include <VoyageWP_Net.hxx>
#include <VoyageMesh_MetricPrcsr.hxx>
#include <VoyageGeo_VelocityBackground.hxx>
#include <VoyageMesh_Element.hxx>
#include <VoyageMesh_RefEdge.hxx>
#include <VoyageMesh_Node.hxx>
#include <VoyageGeo_Path2.hxx>
#include <VoyageGeo_Earth.hxx>
#include <Voyage_MetricInfo.hxx>
#include <Voyage_Edge.hxx>
#include <Voyage_Node.hxx>
#include <Aft_Tools.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <GeoMesh2d_Data.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <Cad_GeomSurface.hxx>
#include <Pln_Edge.hxx>
#include <Geo2d_DelTri.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <TecPlot.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <set>

#include <opencascade/Geom_Surface.hxx>
#include <opencascade/gp_Trsf2d.hxx>
#include <opencascade/gp_Ax2d.hxx>

std::shared_ptr<tnbLib::Entity2d_Box> 
tnbLib::Voyage_Tools::RetrieveDomain
(
	const VoyageGeo_Earth& theEarth
)
{
	Debug_Null_Pointer(theEarth.Surface());
	auto bObj = theEarth.Surface()->ParametricBoundingBox();
	auto t = std::make_shared<Entity2d_Box>(std::move(bObj));
	return std::move(t);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::Voyage_Tools::RetrieveGeometry
(
	const std::vector<std::shared_ptr<VoyageMesh_Node>>& theNodes
)
{
	std::vector<Pnt2d> pnts;
	pnts.reserve(theNodes.size());
	for (const auto& x : theNodes)
	{
		Debug_Null_Pointer(x);
		const auto& coord = x->Coord();
		pnts.push_back(coord);
	}
	return std::move(pnts);
}

std::vector<tnbLib::Pnt3d> 
tnbLib::Voyage_Tools::RetrieveGeometry3d
(
	const std::vector<std::shared_ptr<VoyageMesh_Node>>& theNodes
)
{
	std::vector<Pnt3d> pnts;
	pnts.reserve(theNodes.size());
	for (const auto& x : theNodes)
	{
		Debug_Null_Pointer(x);
		pnts.push_back(x->Coord3D());
	}
	return std::move(pnts);
}

std::vector<tnbLib::connectivity::triple> 
tnbLib::Voyage_Tools::RetrieveTriangleConnectivities
(
	const std::vector<std::shared_ptr<VoyageMesh_Node>>& theNodes, 
	const std::vector<std::shared_ptr<VoyageMesh_Element>>& theElements
)
{
	auto ids = Aft_Tools::RetrieveTriangleConnectivities(theNodes, theElements);
	return std::move(ids);
}

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

std::vector<std::shared_ptr<tnbLib::VoyageMesh_Node>>
tnbLib::Voyage_Tools::RetrieveNodes(const std::vector<std::shared_ptr<VoyageMesh_Element>>& theElements)
{
	static auto cmp = [](const std::shared_ptr<VoyageMesh_Node>& theNode0, const std::shared_ptr<VoyageMesh_Node>& theNode1)
	{
		Debug_Null_Pointer(theNode0);
		Debug_Null_Pointer(theNode1);
		return theNode0->Index() < theNode1->Index();
	};
	std::set<std::shared_ptr<VoyageMesh_Node>, decltype(cmp)> compact(cmp);
	for (const auto& x : theElements)
	{
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		const auto& n2 = x->Node2();
		compact.insert(n0);
		compact.insert(n1);
		compact.insert(n2);
	}
	std::vector<std::shared_ptr<VoyageMesh_Node>> nodes;
	std::copy(compact.begin(), compact.end(), std::back_inserter(nodes));
	std::sort(nodes.begin(), nodes.end(), cmp);
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::VoyageMesh_Edge>> 
tnbLib::Voyage_Tools::RetrieveRefEdges
(
	const std::vector<std::shared_ptr<VoyageMesh_Element>>& theElements
)
{
	std::vector<std::shared_ptr<VoyageMesh_Edge>> edges;
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		auto [e0, e1, e2] = x->Edges();
		if (auto ref = std::dynamic_pointer_cast<VoyageMesh_RefEdge>(e0))
		{
			edges.push_back(ref);
			continue;
		}
		if (auto ref = std::dynamic_pointer_cast<VoyageMesh_RefEdge>(e1))
		{
			edges.push_back(ref);
			continue;
		}
		if (auto ref = std::dynamic_pointer_cast<VoyageMesh_RefEdge>(e2))
		{
			edges.push_back(ref);
			continue;
		}
	}
	return std::move(edges);
}

//std::vector<std::shared_ptr<tnbLib::VoyageMesh_Node>>
//tnbLib::Voyage_Tools::RetrieveNodes(const std::vector<std::shared_ptr<VoyageMesh_Element>>& theElements)
//{
//	static auto cmp = [](const std::shared_ptr<VoyageMesh_Node>& theNode0, const std::shared_ptr<VoyageMesh_Node>& theNode1)
//	{
//		Debug_Null_Pointer(theNode0);
//		Debug_Null_Pointer(theNode1);
//		return theNode0->Index() < theNode1->Index();
//	};
//	std::set<std::shared_ptr<VoyageMesh_Node>, decltype(cmp)> compact(cmp);
//	for (const auto& x : theElements)
//	{
//		const auto& n0 = x->Node0();
//		const auto& n1 = x->Node1();
//		const auto& n2 = x->Node2();
//		compact.insert(n0);
//		compact.insert(n1);
//		compact.insert(n2);
//	}
//	std::vector<std::shared_ptr<VoyageMesh_Node>> nodes;
//	std::copy(compact.begin(), compact.end(), std::back_inserter(nodes));
//	std::sort(nodes.begin(), nodes.end(), cmp);
//	return std::move(nodes);
//}

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
	if (NOT thePolygons.size())
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

		const auto dist = theMetric.CalcDistance(p0, p1);
		tot_dist += dist;
	}
	return tot_dist;
}

Standard_Real tnbLib::Voyage_Tools::CalcDistance(const Pnt2d& theP0, const Pnt2d& theP1)
{
	constexpr auto radioTerrestre = 6372797.56085;

	const auto latitude1 = Geo_Tools::DegToRadian(theP0.X());
	const auto longitude1 = Geo_Tools::DegToRadian(theP0.Y());

	const auto latitude2 = Geo_Tools::DegToRadian(theP1.X());
	const auto longitude2 = Geo_Tools::DegToRadian(theP1.Y());

	const auto haversine =
		std::pow(std::sin((1.0 / 2.0) * (latitude2 - latitude1)), 2) +
		std::cos(latitude1) * std::cos(latitude2) * std::pow(std::sin(1.0 / 2.0 * (longitude2 - longitude1)), 2);

	const auto temp = 2.0 * std::asin(std::min(1.0, std::sqrt(haversine)));
	const auto distancia_puntos = radioTerrestre * temp;

	return distancia_puntos;
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
	t.resize(thePolygon.NbPoints());
	t.at(0) = 0;
	Standard_Real tot_dis = 0.;
	for (size_t i = 1; i < pnts.size(); i++)
	{
		const auto& p0 = pnts.at(i - 1);
		const auto& p1 = pnts.at(i);
		auto dis = theMetric.CalcDistance(p0, p1);
		tot_dis += dis;
		t.at(i) = tot_dis;
	}
	for (auto& x : t)
	{
		x /= tot_dis;
	}
	t.at(t.size() - 1) = 1.0;
	theTotLen = tot_dis;
	return std::move(t);
}

std::shared_ptr<tnbLib::VoyageMesh_MetricPrcsr>
tnbLib::Voyage_Tools::MakeMetricPrcsr
(
	const std::shared_ptr<Geo2d_SizeFunction>& theFun, 
	const VoyageGeo_Earth& theEarth,
	const Voyage_MetricInfo& theInfo
)
{
	auto metrics = theEarth.GetMetrics();
	Debug_Null_Pointer(metrics);
	auto metricInfo =
		std::make_shared<Aft_MetricPrcsrAnIso_Info>
		(
			theInfo.MetricInfo(),
			theInfo.NbSamples(),
			theInfo.NbMetricIters(),
			theInfo.MetricTol()
			);
	auto prcsr = 
		std::make_shared<VoyageMesh_MetricPrcsr>
	(theFun, metrics, metricInfo);
	return std::move(prcsr);
}

std::shared_ptr<tnbLib::Geo2d_SizeFunction>
tnbLib::Voyage_Tools::MakeUniformSizeMap
(
	const VoyageGeo_Earth& theEarth,
	const Standard_Real theSize
)
{
	return std::make_shared<GeoSizeFun2d_Uniform>
	(theSize, theEarth.Surface()->ParametricBoundingBox());
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

std::vector<tnbLib::Pnt2d>
tnbLib::Voyage_Tools::ConvertToVoyageSystem
(
	const std::vector<Pnt2d>& thePnts
)
{
	std::vector<Pnt2d> coords;
	coords.reserve(thePnts.size());
	for (const auto& x:thePnts)
	{
		coords.emplace_back(ConvertToVoyageSystem(x));
	}
	return std::move(coords);
}

std::shared_ptr<tnbLib::Entity2d_Triangulation> 
tnbLib::Voyage_Tools::ConvertToVoyageSystem
(
	const Entity2d_Triangulation& theTriangulation
)
{
	auto indices = theTriangulation.Connectivity();
	std::vector<Pnt2d> coords;
	coords.reserve(theTriangulation.NbPoints());
	for (const auto& x : theTriangulation.Points())
	{
		auto pt = ConvertToVoyageSystem(x);
		coords.push_back(std::move(pt));
	}
	auto tri = 
		std::make_shared<Entity2d_Triangulation>
		(std::move(coords), std::move(indices));
	return std::move(tri);
}

tnbLib::Pnt2d
tnbLib::Voyage_Tools::ConvertVoyageToGlobal(const Pnt2d& xy)
{
	const double signLat = xy.X() >= 0 ? 1.0 : -1.0;
	const double signLon = xy.Y() >= 0 ? 1.0 : -1.0;
	const auto dx = CalcDistance({ 0,0 }, { xy.X(), 0 });
	const auto dy = CalcDistance({ 0,0 }, { 0, xy.Y() });
	return { signLat * dx, signLon * dy };
}

Standard_Real 
tnbLib::Voyage_Tools::KtsToKmh(const Standard_Real x)
{
	return 1.852 * x;
}

std::shared_ptr<tnbLib::Entity2d_Triangulation> 
tnbLib::Voyage_Tools::RetrieveTriangulation2d
(
	const std::vector<std::shared_ptr<VoyageMesh_Element>>& theElements
)
{
	auto nodes = RetrieveNodes(theElements);
	auto points = RetrieveGeometry(nodes);

	auto indices = RetrieveTriangleConnectivities(nodes, theElements);

	auto tri = 
		std::make_shared<Entity2d_Triangulation>
		(std::move(points), std::move(indices));
	return std::move(tri);
}

std::shared_ptr<tnbLib::Entity3d_Triangulation> 
tnbLib::Voyage_Tools::RetrieveTriangulation3d
(
	const std::vector<std::shared_ptr<VoyageMesh_Element>>& theElements
)
{
	auto nodes = RetrieveNodes(theElements);
	auto points = RetrieveGeometry3d(nodes);

	auto indices = RetrieveTriangleConnectivities(nodes, theElements);

	auto tri =
		std::make_shared<Entity3d_Triangulation>
		(std::move(points), std::move(indices));
	return std::move(tri);
}

tnbLib::Dir2d
tnbLib::Voyage_Tools::CalcTangent
(
	const Pnt2d& theP0,
	const Pnt2d& theP1,
	const Pnt2d& theP2
)
{
	const Dir2d dir0(theP0, theP1);
	const Dir2d dir1(theP1, theP2);
	const auto n0 = Vec2d(Dir2d(dir0.Rotated(PI_2)));
	const auto n1 = Vec2d(Dir2d(dir1.Rotated(PI_2)));
	const auto normal = MEAN(n0, n1);
	const auto tang = normal.Rotated(-PI_2);
	return Dir2d(tang.XY());
}

void tnbLib::Voyage_Tools::CalcCoord3d
(
	const std::vector<std::shared_ptr<VoyageMesh_Node>>& theNodes,
	const Cad_GeomSurface& theSurface
)
{
	for (const auto& n : theNodes)
	{
		Debug_Null_Pointer(n);
		n->SetCoord3D(theSurface.Value(n->Coord()));
	}
}

void tnbLib::Voyage_Tools::CalcCoord3d
(
	const std::vector<std::shared_ptr<VoyageMesh_Node>>& theNodes, 
	const VoyageGeo_Earth& theEarth
)
{
	const auto surface = theEarth.Surface();
	Debug_Null_Pointer(surface);
	CalcCoord3d(theNodes, *surface);
}

Standard_Real 
tnbLib::Voyage_Tools::CalcTurningAngle
(
	const Pnt2d& theP0, 
	const Pnt2d& theP1, 
	const Pnt2d& theP2
)
{
	
	const Vec2d v0(theP0, theP1);
	const Vec2d v1(theP1, theP2);
	const auto angle = v0.Angle(v1);
	if (angle < 0)
	{// turns right
		return angle + PI;
	}
	else
	{// turns left
		return angle - PI;
	}
	//const auto n = v0.Crossed(v1);
	//if (std::abs(n) <= 1.0E-6)
	//{
	//	return 0;
	//}
	//const auto angle = v0.Angle(v1);
	//if (n < 0)
	//{// turns right
	//	std::cout << "turning right = " << angle << std::endl;
	//	return PI - angle;
	//}
	//else
	//{// turns left
	//	std::cout << "turning left = " << angle << std::endl;
	//	return PI + angle;
	//}
	//const Dir2d dir(theP0, theP1);
	//gp_Trsf2d trsf;
	//trsf.SetTransformation(gp::OX2d(), gp_Ax2d(theP0, dir));
	//const auto p0 = theP0.Transformed(trsf);
	//const auto p1 = theP1.Transformed(trsf);
	//const auto p2 = theP2.Transformed(trsf);
	//std::cout << "#######################" << std::endl;
	//std::cout << "p0 = " << p0 << std::endl;
	//std::cout << "p1 = " << p1 << std::endl;
	//std::cout << "p2 = " << p2 << std::endl;
	//std::cout << "#######################" << std::endl;
	//const auto dx = p2.X() - p1.X();
	//const auto dy = p2.Y() - p1.Y();
	//// if the angle < 0 it means that the turning diretion would be toward starboard. [9/11/2023 Payvand]
	//const auto angle = std::atan(dy / dx);
	//if (angle < 0)
	//{
	//	return PI + angle;
	//}
	//else
	//{
	//	return PI + angle;
	//}
}

void tnbLib::Voyage_Tools::ConvertToVoyageSystem
(
	const std::shared_ptr<VoyageWP_Net>& theNet
)
{
	static auto convert_coordinate = [](const std::shared_ptr<VoyageWP_Net::RefNode>& node)
	{
		Debug_Null_Pointer(node);
		if (const auto interior = std::dynamic_pointer_cast<VoyageWP_Net::InterNode>(node))
		{
			const auto wps = interior->RetrieveNodes();
			for (const auto& wp: wps)
			{
				Debug_Null_Pointer(wp);
				auto converted = ConvertToVoyageSystem(wp->Coord());
				wp->SetCoord(std::move(converted));
			}
		}
		else
		{
			node->SetCoord(ConvertToVoyageSystem(node->Coord()));
		}
	};
	if (NOT theNet)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the net is empty." << endl
			<< abort(FatalError);
	}
	const auto& nodes = theNet->Nodes();
	for (const auto& x:nodes)
	{
		Debug_Null_Pointer(x);
		convert_coordinate(x);
	}
}