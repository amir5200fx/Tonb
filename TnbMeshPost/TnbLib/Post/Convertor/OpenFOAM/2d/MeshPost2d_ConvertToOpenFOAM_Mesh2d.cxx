#include <MeshPost2d_ConvertToOpenFOAM.hxx>

#include <Entity2d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::tuple
<
	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Element2d>>,
	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Edge2d>>,
	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Node2d>>
>
tnbLib::MeshPost2d_ConvertToOpenFOAM::CalcMesh2d
(
	const Entity2d_Triangulation& theTris,
	const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theBoundaries,
	const std::vector<std::shared_ptr<Node>>& theNodes,
	const Standard_Real theExtrusion
)
{
	auto [vertices, segments] = CalcGragh(theTris, theBoundaries);
	auto nodes2d = CalcNodes2d(theNodes);

	// calculate 2d edges [6/28/2023 Payvand]
	std::vector<std::shared_ptr<Edge2d>> edges;
	edges.resize(segments.size());
	for (const auto& x : segments)
	{
		const auto& v0 = x->Vertices().at(0);
		const auto& v1 = x->Vertices().at(1);

		auto id = x->Index();
		std::array<std::shared_ptr<Node2d>, Edge2d::nbNodes> paired =
		{ nodes2d.at(Index_Of(v0->Index())), nodes2d.at(Index_Of(v1->Index())) };

		auto edge = std::make_shared<Edge2d>(id, std::move(paired));
		edges.at(Index_Of(id)) = std::move(edge);
	}
	std::vector<std::shared_ptr<Element2d>> tris;
	tris.reserve(theTris.NbConnectivity());
	Standard_Integer k = 0;
	for (const auto& x : theTris.Connectivity())
	{
		auto v0 = Index_Of(x.Value(0));
		auto v1 = Index_Of(x.Value(1));
		auto v2 = Index_Of(x.Value(2));

		std::shared_ptr<Edge2d> edge0, edge1, edge2;
		{
			auto seg = RetrieveSegment(vertices.at(v0), vertices.at(v1));
			auto id = seg->Index();
			edge0 = edges.at(Index_Of(id));
		}
		{
			auto seg = RetrieveSegment(vertices.at(v1), vertices.at(v2));
			auto id = seg->Index();
			edge1 = edges.at(Index_Of(id));
		}
		{
			auto seg = RetrieveSegment(vertices.at(v2), vertices.at(v0));
			auto id = seg->Index();
			edge2 = edges.at(Index_Of(id));
		}

		std::array<std::shared_ptr<Edge2d>, Element2d::nbEdges> t =
		{ std::move(edge0),std::move(edge1),std::move(edge2) };
		auto tri = std::make_shared<Element2d>(++k, std::move(t));
		tris.push_back(std::move(tri));
	}
	k = 0;
	for (const auto& x : theTris.Connectivity())
	{
		auto v0 = Index_Of(x.Value(0));
		auto v1 = Index_Of(x.Value(1));
		auto v2 = Index_Of(x.Value(2));

		const auto& tri = tris.at(k++);

		std::shared_ptr<Edge2d> edge0, edge1, edge2;
		{
			auto seg = RetrieveSegment(vertices.at(v0), vertices.at(v1));
			auto sense = seg->ChackSense(vertices.at(v0), vertices.at(v1));
			auto id = seg->Index();
			edge0 = edges.at(Index_Of(id));
			Debug_Null_Pointer(edge0);
			sense ? edge0->SetOwner(tri) : edge0->SetNeighbor(tri);
			if (NOT sense) edge0->SetSense(Standard_False);
		}
		{
			auto seg = RetrieveSegment(vertices.at(v1), vertices.at(v2));
			auto sense = seg->ChackSense(vertices.at(v1), vertices.at(v2));
			auto id = seg->Index();
			edge1 = edges.at(Index_Of(id));
			Debug_Null_Pointer(edge1);
			sense ? edge1->SetOwner(tri) : edge1->SetNeighbor(tri);
			if (NOT sense) edge1->SetSense(Standard_False);
		}
		{
			auto seg = RetrieveSegment(vertices.at(v2), vertices.at(v0));
			auto sense = seg->ChackSense(vertices.at(v2), vertices.at(v0));
			auto id = seg->Index();
			edge2 = edges.at(Index_Of(id));
			Debug_Null_Pointer(edge2);
			sense ? edge2->SetOwner(tri) : edge2->SetNeighbor(tri);
			if (NOT sense) edge2->SetSense(Standard_False);
		}
	}
	auto t = std::make_tuple(std::move(tris), std::move(edges), std::move(nodes2d));
	return std::move(t);
}