#include <Voyage_Tools.hxx>

#include <VoyageGeo_VelocityBackground.hxx>
#include <Voyage_Edge.hxx>
#include <Voyage_Node.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Cad_GeomSurface.hxx>
#include <Geo2d_DelTri.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity2d_Triangulation.hxx>
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