#include <Voyage_Tools.hxx>

#include <VoyageGeo_VelocityBackground.hxx>
#include <Voyage_Edge.hxx>
#include <Voyage_Node.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Geo2d_DelTri.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity2d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <set>

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