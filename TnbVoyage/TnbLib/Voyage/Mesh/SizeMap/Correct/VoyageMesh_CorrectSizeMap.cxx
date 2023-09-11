#include <VoyageMesh_CorrectSizeMap.hxx>

#include <Voyage_Tools.hxx>
#include <Voyage_MetricInfo.hxx>
#include <VoyageGeo_Path2.hxx>
#include <VoyageGeo_Earth.hxx>
#include <MeshBase_Tools.hxx>
#include <Mesh_SetSourcesNode.hxx>
#include <GeoMesh2d_Background.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>
#include <Pln_Edge.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <Geo2d_BalPrTree.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo2d_DelTri.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Ray.hxx>
#include <Dir2d.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <set>

unsigned short tnbLib::VoyageMesh_CorrectSizeMap::verbose = 0;

Standard_Integer tnbLib::VoyageMesh_CorrectSizeMap::DEFAULT_MAX_NB_CORRS(5);

Standard_Real tnbLib::VoyageMesh_CorrectSizeMap::DEFAULT_BASE_SIZE(10.E-3);
Standard_Real tnbLib::VoyageMesh_CorrectSizeMap::DEFAULT_SMOOTHING_FACTOR(0.25);

tnbLib::Pnt2d 
tnbLib::VoyageMesh_CorrectSizeMap::Edge::CalcCentre() const
{
	Debug_Null_Pointer(Node0());
	Debug_Null_Pointer(Node1());
	auto c = MEAN(Node0()->Coord(), Node1()->Coord());
	return std::move(c);
}

tnbLib::Dir2d 
tnbLib::VoyageMesh_CorrectSizeMap::Edge::CalcNormal() const
{
	Debug_Null_Pointer(Node0());
	Debug_Null_Pointer(Node1());
	auto dir = Dir2d(Node0()->Coord(), Node1()->Coord());
	dir.Rotate(0.5 * PI);
	return std::move(dir);
}

std::vector<std::shared_ptr<tnbLib::Entity2d_Polygon>> 
tnbLib::VoyageMesh_CorrectSizeMap::RetrievePolygons() const
{
	std::vector<std::shared_ptr<Entity2d_Polygon>> polygons;
	for (const auto& x : Path()->Curves())
	{
		Debug_Null_Pointer(x);
		const auto& mesh = x->Mesh();
		if (NOT mesh)
		{
			FatalErrorIn(FunctionSIG)
				<< "no mesh has been found for the curve." << endl
				<< abort(FatalError);
		}
		polygons.push_back(mesh);
	}
	return std::move(polygons);
}

std::vector<std::shared_ptr<tnbLib::VoyageMesh_CorrectSizeMap::AngleBisect>> 
tnbLib::VoyageMesh_CorrectSizeMap::CalcBisectAngles() const
{
	std::vector<std::shared_ptr<AngleBisect>> angles;
	auto polygons = RetrievePolygons();
	if (Direction() IS_EQUAL PathDirect::Port)
	{
		std::reverse(polygons.begin(), polygons.end());
		for (const auto& x : polygons)
		{
			Debug_Null_Pointer(x);
			x->Reverse();
		}
	}
	std::vector<std::shared_ptr<Chain>> chains;
	for (const auto& x : polygons)
	{
		auto chain = CalcChain(*x);
		chains.push_back(std::move(chain));
	}
	for (size_t i = 1; i < chains.size(); i++)
	{
		const auto& ch0 = chains.at(i - 1);
		const auto& ch1 = chains.at(i);
		auto angle = CalcAngle(ch0, ch1);
		angles.push_back(std::move(angle));
	}
	// reverse back the polygons [9/3/2023 Payvand]
	if (Direction() IS_EQUAL PathDirect::Port)
	{
		std::reverse(polygons.begin(), polygons.end());
		for (const auto& x : polygons)
		{
			Debug_Null_Pointer(x);
			x->Reverse();
		}
	}
	return std::move(angles);
}

std::vector<std::shared_ptr<tnbLib::VoyageMesh_CorrectSizeMap::Chain>> 
tnbLib::VoyageMesh_CorrectSizeMap::CalcEdges() const
{
	auto polygons = RetrievePolygons();
	std::vector<std::shared_ptr<Chain>> chains;
	chains.reserve(polygons.size());
	for (const auto& x : polygons)
	{
		Debug_Null_Pointer(x);
		auto chain = CalcChain(*x);
		chains.push_back(std::move(chain));
	}
	return std::move(chains);
}

std::shared_ptr<tnbLib::VoyageMesh_CorrectSizeMap::Edge> 
tnbLib::VoyageMesh_CorrectSizeMap::LastEdge
(
	const Chain& theChain
)
{
	const auto& edges = theChain.Edges();
	return edges.at(edges.size() - 1);
}

std::shared_ptr<tnbLib::Entity2d_Ray> 
tnbLib::VoyageMesh_CorrectSizeMap::CalcBisectRay
(
	const Pnt2d& theP0, 
	const Pnt2d& theP1, 
	const Pnt2d& theP2,
	Standard_Real& theAngle
)
{
	auto dir0 = Dir2d(theP0, theP1);
	auto dir1 = Dir2d(theP1, theP2);
	auto n = dir0.Crossed(dir1);
	Dir2d bisect;
	if (n <= 0)
	{ // the angle is less than 180 deg. [8/30/2023 aamir]
		auto angle = std::abs(dir0.Angle(dir1));
		auto alpha = PI - angle;
		theAngle = alpha;
		auto rotated_angle = angle + 0.5 * alpha;
		bisect = dir0.Rotated(-rotated_angle);
	}
	else
	{// the angle is grater than 180 [8/30/2023 aamir]
		auto angle = std::abs(dir0.Angle(dir1));
		auto alpha = PI + angle;
		theAngle = alpha;
		auto rotated_angle = angle + 0.5 * alpha;
		bisect = dir0.Rotated(rotated_angle);
	}
	auto centre = theP1;
	auto ray = std::make_shared<Entity2d_Ray>(std::move(centre), std::move(bisect));
	return std::move(ray);
}

std::shared_ptr<tnbLib::Entity2d_Ray> 
tnbLib::VoyageMesh_CorrectSizeMap::CalcBisectRay
(
	const Edge& theEdge0, 
	const Edge& theEdge1,
	Standard_Real& theAngle
)
{
	const auto& node0 = theEdge0.Node0();
	const auto& node2 = theEdge1.Node1();
	const auto& node1 = theEdge0.Node1();

	const auto& p0 = node0->Coord();
	const auto& p1 = node1->Coord();
	const auto& p2 = node2->Coord();
	auto ray = CalcBisectRay(p0, p1, p2, theAngle);
	return std::move(ray);
}

std::shared_ptr<tnbLib::VoyageMesh_CorrectSizeMap::AngleBisect> 
tnbLib::VoyageMesh_CorrectSizeMap::CalcAngle
(
	const std::shared_ptr<Chain>& thePoly0,
	const std::shared_ptr<Chain>& thePoly1
)
{
	auto edge0 = LastEdge(*thePoly0);
	auto edge1 = LastEdge(*thePoly1);
	Standard_Real angle;
	auto ray = CalcBisectRay(*edge0, *edge1, angle);
	auto t = std::make_shared<AngleBisect>(ray, thePoly0, thePoly1);
	t->SetAngle(angle);
	return std::move(t);
}

std::shared_ptr<tnbLib::VoyageMesh_CorrectSizeMap::Chain> 
tnbLib::VoyageMesh_CorrectSizeMap::CalcChain
(
	const Entity2d_Polygon& thePolygon
)
{
	std::vector<std::shared_ptr<Node>> nodes;
	nodes.reserve(thePolygon.NbPoints());
	Standard_Integer k = 0;
	for (const auto& x : thePolygon.Points())
	{
		auto node = std::make_shared<Node>(++k, x);
		nodes.push_back(std::move(node));
	}
	std::vector<std::shared_ptr<Edge>> edges;
	edges.reserve(thePolygon.NbPoints() - 1);
	for (size_t i = 1; i < nodes.size(); i++)
	{
		const auto& n0 = nodes.at(i - 1);
		const auto& n1 = nodes.at(i);
		auto edge = std::make_shared<Edge>(n0, n1);
		edges.push_back(std::move(edge));
	}
	auto chain = std::make_shared<Chain>(std::move(edges));
	return std::move(chain);
}

std::vector<std::shared_ptr<tnbLib::VoyageMesh_CorrectSizeMap::Node>>
tnbLib::VoyageMesh_CorrectSizeMap::RetrieveNodes
(
	const std::vector<std::shared_ptr<Edge>>& theEdges
)
{
	std::vector<std::shared_ptr<Node>> nodes;
	nodes.reserve(theEdges.size() + 1);
	Debug_Null_Pointer(theEdges.at(0));
	nodes.push_back(theEdges.at(0)->Node0());
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		nodes.push_back(x->Node1());
	}
	return std::move(nodes);
}

std::pair<Standard_Real, Standard_Boolean> 
tnbLib::VoyageMesh_CorrectSizeMap::CalcDistance
(
	const Edge& theEdge, 
	const Entity2d_Ray& theRay,
	const Geo2d_MetricPrcsrAnIso& theMetrics,
	const Standard_Boolean reverse_normal
)
{
	auto centre = theEdge.CalcCentre();
	auto normal = theEdge.CalcNormal();
	if (reverse_normal) normal = -normal;
	Entity2d_Ray normal_ray(std::move(centre), std::move(normal));
	auto [intPoint, intsect] = Geo_Tools::CalcIntersectionPoint_cgal(theRay, normal_ray);
	if (intsect)
	{
		return { theMetrics.CalcDistance(intPoint, centre),Standard_True };
	}
	else
	{
		return { RealLast(),Standard_False };
	}
}

std::vector<tnbLib::Pnt2d> 
tnbLib::VoyageMesh_CorrectSizeMap::RetrieveCoords
(
	const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePolygons
)
{
	std::vector<Pnt2d> coords;
	for (const auto& poly : thePolygons)
	{
		for (const auto& x : poly->Points())
		{
			coords.push_back(x);
		}
	}
	return std::move(coords);
}

namespace tnbLib
{
	typedef Mesh_SetSourcesNode<Pnt2d, void> sourceNode;
	typedef Mesh_SetSourcesNode<Pnt2d, Standard_Real> hNode;

	namespace corrSizeMapTools
	{

		void InsertToEngine(Pnt2d&& theCoord, const Standard_Real theTol, Geo_AdTree<std::shared_ptr<Pnt2d>>& engine)
		{
			auto b = Geo_BoxTools::GetBox<Pnt2d>(theCoord, theTol);

			std::vector<std::shared_ptr<Pnt2d>> items;
			engine.GeometrySearch(b, items);
			if (items.empty())
			{
				auto node = std::make_shared<Pnt2d>(std::move(theCoord));
				Debug_Null_Pointer(node);
				engine.InsertToGeometry(node);
			}
			else
			{
				Standard_Real minDis = RealLast();
				for (const auto& i : items)
				{
					auto dis = i->Distance(theCoord);
					if (dis < minDis)
					{
						minDis = dis;
					}
				}
				if (minDis > theTol)
				{
					auto node = std::make_shared<Pnt2d>(std::move(theCoord));
					Debug_Null_Pointer(node);
					engine.InsertToGeometry(node);
				}
				else
				{
					// do nothing [8/25/2022 Amir]
				}
			}
		}

		void InsertCorners(Geo_AdTree<std::shared_ptr<Pnt2d>>& theEngine)
		{
			const auto& b = theEngine.GeometryBoundingBox();
			{
				auto pt = b.Corner(Box2d_PickAlgorithm_SW);
				auto node = std::make_shared<Pnt2d>(std::move(pt));
				theEngine.InsertToGeometry(node);
			}
			{
				auto pt = b.Corner(Box2d_PickAlgorithm_SE);
				auto node = std::make_shared<Pnt2d>(std::move(pt));
				theEngine.InsertToGeometry(node);
			}
			{
				auto pt = b.Corner(Box2d_PickAlgorithm_NE);
				auto node = std::make_shared<Pnt2d>(std::move(pt));
				theEngine.InsertToGeometry(node);
			}
			{
				auto pt = b.Corner(Box2d_PickAlgorithm_NW);
				auto node = std::make_shared<Pnt2d>(std::move(pt));
				theEngine.InsertToGeometry(node);
			}
		}

		auto RetrieveNodes
		(
			const Geo2d_BalPrTree<std::shared_ptr<sourceNode>>& theEngine,
			/*const std::vector<Pnt2d>& theCoords,*/
			const Entity2d_Box& theDomain,
			const Standard_Real theTol
		)
		{
			std::vector<Geo2d_BalPrTree<std::shared_ptr<sourceNode>>::leafNode*> leaves;
			theEngine.RetrieveLeavesTo(leaves);

			std::vector<std::shared_ptr<Entity2d_Box>> boxes;
			boxes.reserve(leaves.size());
			for (const auto& x : leaves)
			{
				Debug_Null_Pointer(x);
				const auto& b = x->Box();
				boxes.push_back(b);
			}

			Geo_AdTree<std::shared_ptr<Pnt2d>> engine;
			engine.SetGeometryCoordFunc
			([](const std::shared_ptr<Pnt2d>& x)-> const auto& {return *x; });
			engine.SetGeometryRegion(theDomain);

			InsertCorners(engine);

			for (const auto& x : boxes)
			{
				auto p0 = x->Corner(Box2d_PickAlgorithm_SW);
				auto p1 = x->Corner(Box2d_PickAlgorithm_SE);
				auto p2 = x->Corner(Box2d_PickAlgorithm_NE);
				auto p3 = x->Corner(Box2d_PickAlgorithm_NW);

				InsertToEngine(std::move(p0), theTol, engine);
				InsertToEngine(std::move(p1), theTol, engine);
				InsertToEngine(std::move(p2), theTol, engine);
				InsertToEngine(std::move(p3), theTol, engine);

			}

			std::vector<std::shared_ptr<Pnt2d>> items;
			engine.RetrieveFromGeometryTo(items);

			std::vector<Pnt2d> coords;
			coords.reserve(items.size());
			for (const auto& x : items)
			{
				coords.push_back(*x);
			}
			return std::move(coords);
		}
	}
}

void tnbLib::VoyageMesh_CorrectSizeMap::Perform()
{
	if (NOT Path())
	{
		FatalErrorIn(FunctionSIG)
			<< "No path has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT SizeFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "No size function has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT GetInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric info has been loaded." << endl
			<< abort(FatalError);
	}
	const auto& path = Path();
	const auto& sizeFun = SizeFun();

	auto bisectAngles = CalcBisectAngles();
	
	for (const auto& x : bisectAngles)
	{
		std::cout << "angle = " << Geo_Tools::RadianToDegree(x->Angle()) << std::endl;
	}
	PAUSE;
	//auto chain = CalcEdges();
	auto polygons = RetrievePolygons();
	auto coords = RetrieveCoords(polygons);
	//auto d = Geo_BoxTools::GetBox(coords, 1.0E-4);
	auto d = *Voyage_Tools::RetrieveDomain(*path->Earth());

	Geo2d_BalPrTree<std::shared_ptr<sourceNode>> engine;
	engine.SetMaxUnbalancing(2);
	engine.SetGeometryCoordFunc(&sourceNode::GetCoord);
	engine.SetGeometryRegion(d);
	engine.BUCKET_SIZE = 2;

	const Standard_Real mergCrit = 1.0E-4 * d.Diameter();
	{// approximation scope [8/19/2023 aamir]
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);
		for (const auto& x : coords)
		{
			auto b = Geo_BoxTools::GetBox<Pnt2d>(x, mergCrit);
			std::vector<std::shared_ptr<sourceNode>> items;
			engine.GeometrySearch(b, items);
			if (items.empty())
			{
				auto node = std::make_shared<sourceNode>(x);
				Debug_Null_Pointer(node);
				engine.InsertToGeometry(node);
			}
			else
			{
				Standard_Real minDis = RealLast();
				for (const auto& i : items)
				{
					auto dis = i->Coord().Distance(x);
					if (dis < minDis)
					{
						minDis = dis;
					}
				}
				if (minDis > mergCrit)
				{
					auto node = std::make_shared<sourceNode>(x);
					Debug_Null_Pointer(node);
					engine.InsertToGeometry(node);
				}
				else
				{
					// do nothing [8/19/2023 aamir]
				}
			}
		}
	}

	if (verbose)
	{
		Info << endl
			<< " - the space is approximated in: " << global_time_duration << " ms." << endl;
	}

	if (true)
	{
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			engine.SetMaxUnbalancing(2);
			engine.PostBalance();
		}

		if (verbose)
		{
			Info << endl
				<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
		}
	}

	std::shared_ptr<Entity2d_Triangulation> myTris;
	{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		auto pnts = corrSizeMapTools::RetrieveNodes(engine, d, mergCrit);
		Geo2d_DelTri delTri(pnts);
		delTri.Triangulate();

		myTris = delTri.Data();
	}
	if (verbose)
	{
		Info << endl
			<< " - the domain is triangulated in: " << global_time_duration << " ms." << endl;
	}

	if (verbose)
	{
		Info << " Constructing the background mesh..." << endl;
		Info << endl;
	}

	auto meshData = std::make_shared<GeoMesh2d_Data>();
	Debug_Null_Pointer(meshData);

	// constructing a background mesh data [6/23/2023 Payvand]
	meshData->Construct(*myTris);

	const auto bMesh = std::make_shared<GeoMesh2d_SingleBackground>();
	Debug_Null_Pointer(bMesh);

	bMesh->LoadData(std::move(meshData));

	// initiate the current element [8/1/2022 Amir]
	bMesh->InitiateCurrentElement();
	bMesh->SetBoundingBox(d);
	bMesh->Sources().resize(myTris->NbPoints(), 1.0);

	if (verbose)
	{
		Info << " Setting the sources into the background mesh..." << endl;
		Info << endl;
	}

	auto hvInfo = std::make_shared<GeoMesh_Background_SmoothingHvCorrection_Info>();
	Debug_Null_Pointer(hvInfo);
	hvInfo->SetMaxNbIters(MaxNbCorrs());
	hvInfo->SetFactor(/*SmoothingFactor()*/0.25);

	const auto& earth = path->Earth();
	if (NOT earth)
	{
		FatalErrorIn(FunctionSIG)
			<< "no earth has been found." << endl
			<< abort(FatalError);
	}
	auto metrics = earth->GetMetrics();
	Debug_Null_Pointer(metrics);
	auto uniSizeFun = 
		std::make_shared<GeoSizeFun2d_Uniform>(1.0, d);
	auto metricInfo = 
		std::make_shared<Geo_MetricPrcsrAnIso_Info>
		(GetInfo()->MetricInfo(), GetInfo()->NbSamples());
	auto metricProcsr =
		std::make_shared<Geo2d_MetricPrcsrAnIso>(uniSizeFun, metrics, metricInfo);

	std::vector<std::shared_ptr<hNode>> sources;
	for (const auto& x : bisectAngles)
	{
		if (x->Angle() < PI)
		{
			const auto& ray = x->Ray();
			const auto& poly0 = x->RightSide();
			const auto& poly1 = x->LeftSide();

			for (const auto& edge : poly0->Edges())
			{
				auto centre = edge->CalcCentre();
				auto baseSize = sizeFun->Value(centre);
				auto [dist, insct] = CalcDistance(*edge, *ray, *metricProcsr, Standard_True);
				std::cout << " dist = " << dist << ", insct: " << insct << std::endl;
				if (insct)
				{
					if (dist < baseSize)
					{
						auto source = std::make_shared<hNode>(std::move(centre), dist);
						sources.push_back(std::move(source));
					}
				}
				else
				{
					break;
				}
			}
			for (const auto& edge : poly1->Edges())
			{
				auto centre = edge->CalcCentre();
				auto baseSize = sizeFun->Value(centre);
				auto [dist, insct] = CalcDistance(*edge, *ray, *metricProcsr);
				if (insct)
				{
					if (dist < baseSize)
					{
						auto source = std::make_shared<hNode>(std::move(centre), dist);
						sources.push_back(std::move(source));
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	//std::cout << "base size = " << BaseSize() << std::endl;
	//std::cout << "size = " << sources.size() << std::endl;;
	Voyage_Tools::SetInverseSourcesToMesh(sources, BaseSize(), hvInfo->Factor(), *bMesh);
	sources.clear();
	//OFstream myFile("correct.plt");
	//bMesh->ExportToPlt(myFile);
	
	if (verbose)
	{
		Info << " Applying Hv-correction..." << endl;
		Info << " - Max. nb. of iterations: " << hvInfo->MaxNbIters() << endl;
		Info << endl;
	}
	for (auto& x : bMesh->Sources())
	{
		x = 1.0 / x;
	}
	bMesh->HvCorrection(hvInfo);
	for (auto& x : bMesh->Sources())
	{
		x = 1.0 / x;
	}
	//bMesh->ExportToPlt(myFile);
	//std::exit(1);
	if (verbose)
	{
		Info << " The Hv-Correction is performed, successfully." << endl;
	}
	theBackMesh_ = std::move(bMesh);
	Change_IsDone() = Standard_True;
}