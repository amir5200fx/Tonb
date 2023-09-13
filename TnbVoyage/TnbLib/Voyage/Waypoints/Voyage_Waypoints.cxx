#include <Voyage_Waypoints.hxx>
#define FULLDEBUG
#include <VoyageWP_PointDistb.hxx>
#include <Voyage_OffsetProfile_Segment.hxx>
#include <VoyageWP_Ref.hxx>
#include <VoyageWP_Offset.hxx>
#include <Voyage_MetricInfo.hxx>
#include <Voyage_Mesh.hxx>
#include <Voyage_Tools.hxx>
#include <VoyageMesh_RefEdge.hxx>
#include <VoyageMesh_DepartureNode.hxx>
#include <VoyageMesh_ArrivalNode.hxx>
#include <VoyageMesh_MetricPrcsr.hxx>
#include <VoyageMesh_OptNode_Calculator.hxx>
#include <VoyageMesh_AltrOptNode_NelderMead.hxx>
#include <VoyageMesh_AltrOptNode_SubTri.hxx>
#include <VoyageMesh_OptNode_Altr.hxx>
#include <VoyageGeo_Path2.hxx>
#include <VoyageGeo_Earth.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Cad_Shape.hxx>
#include <Pln_Edge.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::Voyage_Waypoints::verbose(0);

std::vector<std::shared_ptr<tnbLib::Entity2d_Polygon>> 
tnbLib::Voyage_Waypoints::RetrievePolygons
(
	const VoyageGeo_Path2& thePath
)
{
	std::vector<std::shared_ptr<Entity2d_Polygon>> polygons;
	for (const auto& x : thePath.Curves())
	{
		Debug_Null_Pointer(x);
		const auto& mesh = x->Mesh();
		if (NOT mesh)
		{
			FatalErrorIn(FunctionSIG)
				<< "the path is not discretized." << endl
				<< abort(FatalError);
		}
		polygons.push_back(mesh);
	}
	return std::move(polygons);
}

std::pair
<
	std::vector<std::shared_ptr<tnbLib::VoyageMesh_Edge>>,
	std::vector<std::shared_ptr<tnbLib::VoyageMesh_Edge>>
>
tnbLib::Voyage_Waypoints::RetrieveEdges
(
	const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePolygons
)
{
	std::vector<std::shared_ptr<VoyageMesh_Edge>> starboard, port;
	{// the port regions [9/3/2023 Payvand]
		Standard_Integer region_nb = 0;
		for (const auto& x : thePolygons)
		{
			Debug_Null_Pointer(x);
			auto edges = RetrieveEdges(*x);
			region_nb++;
			for (const auto& e : edges)
			{
				Debug_Null_Pointer(e);
				e->SetRegion(region_nb);
				auto ref = std::dynamic_pointer_cast<VoyageMesh_RefEdge>(e);
				Debug_Null_Pointer(ref);
				ref->SetSense(Standard_False);
				port.push_back(std::move(e));
			}
		}
	}
	{// the starboard regions [9/3/2023 Payvand]
		Standard_Integer region_nb = 0;
		auto polygons = thePolygons;
		std::reverse(polygons.begin(), polygons.end());
		for (const auto& x : polygons)
		{
			Debug_Null_Pointer(x);
			x->Reverse();
			auto edges = RetrieveEdges(*x);
			region_nb++;
			for (const auto& e : edges)
			{
				Debug_Null_Pointer(e);
				e->SetRegion(region_nb);
				auto ref = std::dynamic_pointer_cast<VoyageMesh_RefEdge>(e);
				Debug_Null_Pointer(ref);
				//ref->SetSense(Standard_False);
				starboard.push_back(std::move(e));
			}
		}
	}
	SetDeparture(starboard);
	SetDeparture(port);
	SetArrival(starboard);
	SetArrival(port);
	Merge(starboard);
	Merge(port);
	Renumber(starboard);
	Renumber(port);
	auto t = std::make_pair(std::move(starboard), std::move(port));
	return std::move(t);
}

std::vector<std::shared_ptr<tnbLib::VoyageMesh_Edge>> 
tnbLib::Voyage_Waypoints::RetrieveEdges
(
	const Entity2d_Polygon& thePoly
)
{
	const auto& pnts = thePoly.Points();
	std::vector<std::shared_ptr<VoyageMesh_Node>> nodes;
	nodes.reserve(pnts.size());
	Standard_Integer k = 0;
	for (const auto& x : pnts)
	{
		auto node = std::make_shared<VoyageMesh_RefNode>(++k, x);
		nodes.push_back(std::move(node));
	}
	std::vector<std::shared_ptr<VoyageMesh_Edge>> edges;
	for (size_t i = 1; i < nodes.size(); i++)
	{
		const auto& n0 = nodes.at(i - 1);
		const auto& n1 = nodes.at(i);
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		auto edge = std::make_shared<VoyageMesh_RefEdge>(i, n0, n1);
		edges.push_back(std::move(edge));
	}
	return std::move(edges);
}

std::shared_ptr<tnbLib::VoyageMesh_Node> 
tnbLib::Voyage_Waypoints::Merge
(
	const VoyageMesh_Node& theNode0,
	const VoyageMesh_Node& theNode1
)
{
	if (theNode0.Coord().Distance(theNode1.Coord()) > 1.0E-10)
	{
		FatalErrorIn(FunctionSIG)
			<< "Something went wrong." << endl
			<< " - dist = " << theNode0.Coord().Distance(theNode1.Coord()) << endl
			<< abort(FatalError);
	}
	auto pt = MEAN(theNode0.Coord(), theNode1.Coord());
	auto node = std::make_shared<VoyageMesh_RefNode>(0, std::move(pt));
	return std::move(node);
}

std::vector<std::shared_ptr<tnbLib::VoyageMesh_Node>> 
tnbLib::Voyage_Waypoints::RetrieveTipNodes
(
	const std::vector<std::shared_ptr<VoyageMesh_Element>>& theElements
)
{
	std::vector<std::shared_ptr<VoyageMesh_Node>> nodes;
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		auto [n0, n1, n2] = x->Nodes();
		Debug_Null_Pointer(n0);
		if (n0->IsTip())
		{
			nodes.push_back(n0);
			continue;
		}
		Debug_Null_Pointer(n1);
		if (n1->IsTip())
		{
			nodes.push_back(n1);
			continue;
		}
		Debug_Null_Pointer(n2);
		if (n2->IsTip())
		{
			nodes.push_back(n2);
			continue;
		}
	}
	return std::move(nodes);
}

void tnbLib::Voyage_Waypoints::Merge
(
	VoyageMesh_Edge& theEdge0,
	VoyageMesh_Edge& theEdge1
)
{
	const auto& n0 = theEdge0.Node1();
	const auto& n1 = theEdge1.Node0();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	auto node = Merge(*n0, *n1);
	theEdge0.SetNode1(node);
	theEdge1.SetNode0(node);
}

void tnbLib::Voyage_Waypoints::Merge
(
	const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
)
{
	for (size_t i = 1; i < theEdges.size(); i++)
	{
		const auto& e0 = theEdges.at(i - 1);
		const auto& e1 = theEdges.at(i);
		Debug_Null_Pointer(e0);
		Debug_Null_Pointer(e1);
		if (e0->Region() NOT_EQUAL e1->Region())
		{
			Merge(*e0, *e1);
		}
	}
}

void tnbLib::Voyage_Waypoints::SetDeparture
(
	const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
)
{
	auto edge = theEdges.at(0);
	Debug_Null_Pointer(edge);
	auto node = edge->Node0();
	Debug_Null_Pointer(node);
	auto departure = std::make_shared<VoyageMesh_DepartureNode>(node->Index(), node->Coord());
	edge->SetNode0(departure);
}

void tnbLib::Voyage_Waypoints::SetArrival
(
	const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
)
{
	auto edge = theEdges.at(theEdges.size() - 1);
	Debug_Null_Pointer(edge);
	auto node = edge->Node1();
	Debug_Null_Pointer(node);
	auto arrival = std::make_shared<VoyageMesh_ArrivalNode>(node->Index(), node->Coord());
	edge->SetNode1(arrival);
}

void tnbLib::Voyage_Waypoints::Renumber
(
	const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
)
{
	Standard_Integer k = 0;
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Node0());
		x->Node0()->SetIndex(++k);
	}
	Debug_Null_Pointer(theEdges.at(theEdges.size() - 1)->Node1());
	theEdges.at(theEdges.size() - 1)->Node1()->SetIndex(++k);
	k = 0;
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		x->SetIndex(++k);
	}
}

void tnbLib::Voyage_Waypoints::Perform()
{
	typedef std::shared_ptr<VoyageMesh_Element> elm_ptr;
	static auto cmp = [](const elm_ptr& elm0, const elm_ptr& elm1)
	{
		Debug_Null_Pointer(elm0);
		Debug_Null_Pointer(elm1);
		return elm0->Index() < elm1->Index();
	};
	if (NOT Path())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No path has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT GetInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "No metric info has been found." << endl
			<< abort(FatalError);
	}
	if (NOT Size())
	{
		FatalErrorIn(FunctionSIG)
			<< "No size has been set." << endl
			<< abort(FatalError);
	}
	const auto& path = Path();
	if (NOT path->Earth())
	{
		FatalErrorIn(FunctionSIG)
			<< "No earth has been set to the path." << endl
			<< abort(FatalError);
	}
	const auto& earth = path->Earth();
	auto metrics = earth->GetMetrics();
	Debug_Null_Pointer(metrics);
	auto metricInfo =
		std::make_shared<Aft_MetricPrcsrAnIso_Info>
		(
			GetInfo()->MetricInfo(),
			GetInfo()->NbSamples(), 
			GetInfo()->NbMetricIters(),
			GetInfo()->MetricTol()
			);

	auto d = Voyage_Tools::RetrieveDomain(*earth);
	auto polygons = RetrievePolygons(*path);
	if (verbose)
	{
		Info << endl
			<< " - No. of regions in the path: " << polygons.size() << endl;
	}

	auto starboard_metricPrcsr = 
		std::make_shared<VoyageMesh_MetricPrcsr>
		(StarboardSizeFunction(), metrics, metricInfo);
	Debug_Null_Pointer(starboard_metricPrcsr);
	starboard_metricPrcsr->SetDimSize(d->Diameter());

	auto port_metricPrcsr =
		std::make_shared<VoyageMesh_MetricPrcsr>
		(PortSizeFunction(), metrics, metricInfo);
	Debug_Null_Pointer(port_metricPrcsr);
	port_metricPrcsr->SetDimSize(d->Diameter());
	if (verbose)
	{
		Info << endl
			<< " - The metric processor is created." << endl;
	}

	auto optNode_altr_alg = std::make_shared<VoyageMesh_AltrOptNode_SubTri>();
	Debug_Null_Pointer(optNode_altr_alg);
	optNode_altr_alg->SetSizeCorrInfo(GetInfo()->SizeCorrIterInfo());
	optNode_altr_alg->SetNealderMeadInfo(GetInfo()->NelderMeadInfo());
	optNode_altr_alg->SetMaxLev(GetInfo()->MaxSubTriSubdivideLev());

	auto optNode = 
		std::make_shared<VoyageMesh_OptNode_Altr>
		(optNode_altr_alg, GetInfo()->SizeCorrIterInfo());

	if (verbose)
	{
		Info << endl
			<< " - The node calculator is created." << endl;
	}
	if (verbose)
	{
		Info << endl
			<< " # Creating the reference edges..." << endl;
	}
	auto [starboard, port] = RetrieveEdges(polygons);
	if (verbose)
	{
		Info << endl
			<< " - The reference edges are created." << endl;
	}
	std::vector<std::shared_ptr<VoyageMesh_Element>> elements_star;
	{// Starboard region [9/2/2023 Payvand]

		optNode->SetMetricMap(starboard_metricPrcsr);

		const auto alg = std::make_shared<Voyage_Mesh>();
		Debug_Null_Pointer(alg);
		alg->LoadMetricMap(starboard_metricPrcsr);
		alg->LoadRefPath(starboard);
		alg->LoadNodeCalculator(optNode);
		alg->SetMinDistFactor(0.4);
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
			alg->Perform();
		}
		if (verbose)
		{
			Info << endl
				<< " - The starboard side is successfully meshed, in " 
				<< global_time_duration << " ms." << endl;
		}
		const auto& elemMap = alg->RetrieveElements();
		
		elements_star.reserve(elemMap.size());
		for (const auto& x : elemMap)
		{
			elements_star.push_back(x.second);
		}
		std::sort(elements_star.begin(), elements_star.end(), cmp);
		theStarMesh_ = Voyage_Tools::RetrieveTriangulation2d(elements_star);
	}
	std::vector<std::shared_ptr<VoyageMesh_Element>> elements_port;
	{// Port region [9/2/2023 Payvand]

		optNode->SetMetricMap(port_metricPrcsr);

		const auto alg = std::make_shared<Voyage_Mesh>();
		Debug_Null_Pointer(alg);
		alg->LoadMetricMap(port_metricPrcsr);
		alg->LoadRefPath(port);
		alg->LoadNodeCalculator(optNode);
		alg->SetMinDistFactor(0.4);
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
			alg->Perform();
		}
		if (verbose)
		{
			Info << endl
				<< " - The port side is successfully meshed, in " 
				<< global_time_duration << " ms." << endl;
		}
		const auto& elemMap = alg->RetrieveElements();	
		elements_port.reserve(elemMap.size());
		for (const auto& x : elemMap)
		{
			elements_port.push_back(x.second);
		}
		std::sort(elements_port.begin(), elements_port.end(), cmp);
		thePortMesh_ = Voyage_Tools::RetrieveTriangulation2d(elements_port);
	}
	//return;
	//Change_IsDone() = Standard_True;
	if (verbose)
	{
		Info << endl
			<< " # Creating the reference path..." << endl;
	}
	//- Create the voyage ref.
	auto alg_ref = std::make_shared<VoyageWP_Ref>();
	Debug_Null_Pointer(alg_ref);
	alg_ref->CalcReference(starboard, port);
	Debug_If_Condition_Message(NOT alg_ref->IsDone(), "the application is not performed.");
	if (verbose)
	{
		Info << endl
			<< " - The reference path is successfully created." << endl;
	}
	//- Create the offset points
	if (verbose)
	{
		Info << endl
			<< " # Creating the offset points..." << endl;
	}
	auto alg_offsets = std::make_shared<VoyageWP_Offset>();
	Debug_Null_Pointer(alg_offsets);
	alg_offsets->CalcOffsets(*alg_ref);
	Debug_If_Condition_Message(NOT alg_offsets->IsDone(), "the application is not performed.");
	if (verbose)
	{
		Info << endl
			<< " - The offset points are successfully created." << endl;
	}
	auto profile = std::make_shared<Voyage_OffsetProfile_Segment>();
	if (verbose)
	{
		Info << endl
			<< " # Creating the waypoints..." << endl;
	}
	auto alg_distb = std::make_shared<VoyageWP_PointDistb>();
	Debug_Null_Pointer(alg_distb);
	alg_distb->SetEarth(earth);
	alg_distb->SetCurveInfo(GetInfo()->CurveMeshInfo());
	alg_distb->SetIntegInfo(GetInfo()->MetricInfo());
	alg_distb->SetOffsets(alg_offsets);
	alg_distb->SetProfile(profile);
	alg_distb->SetSize(Size());
	alg_distb->Perform();
	Debug_If_Condition_Message(NOT alg_distb->IsDone(), "the application is not performed.");
	if (verbose)
	{
		Info << endl
			<< " - The waypoints are successfully created." << endl;
	}
	OFstream myFile("offsets.plt");
	alg_distb->ExportToPlt(myFile);
	Change_IsDone() = Standard_True;
}