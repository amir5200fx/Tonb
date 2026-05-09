//#include <MeshPost2d_ConvertToOpenFOAM.hxx>
//
//#include <MeshPost2d_OFTopology.hxx>
//#include <MeshIO2d_FEA.hxx>
//#include <Entity2d_Triangulation.hxx>
//#include <TnbError.hxx>
//#include <OSstream.hxx>
//
//std::tuple
//<
//	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Element2d>>,
//	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Edge2d>>,
//	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Node2d>>
//>
//tnbLib::MeshPost2d_ConvertToOpenFOAM::CalcMesh2d
//(
//	const std::vector<std::shared_ptr<Node>>& theNodes
//)
//{
//	auto nodes2d = CalcNodes2d(theNodes);
//	if (NOT Mesh()->MeshIO())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "no triangulation has been found." << endl
//			<< abort(FatalError);
//	}
//	const auto& mesh = Mesh()->MeshIO()->Mesh();
//	if (NOT mesh)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "no triangulation has been found." << endl
//			<< abort(FatalError);
//	}
//	const auto nbIteriors = Mesh()->Interiors().size();
//	auto all_edges = Mesh()->RetrieveEdges();
//	//const auto& int_edges = Mesh()->Interiors();
//	//const auto& bnd_edges = Mesh()->RetrieveBoundaries();
//
//	std::vector<std::shared_ptr<Edge2d>> edges;
//	edges.reserve(all_edges.size());
//	for (const auto& x : all_edges)
//	{
//		auto i0 = x.V0();
//		auto i1 = x.V1();
//
//		auto id = x.Index();
//		std::array<std::shared_ptr<Node2d>, Edge2d::nbNodes> paired =
//		{ nodes2d.at(Index_Of(i0)), nodes2d.at(Index_Of(i1)) };
//
//		auto edge = std::make_shared<Edge2d>(id, std::move(paired));
//		edges.push_back(std::move(edge));
//	}
//	/*for (const auto& x : Mesh()->Boundaries())
//	{
//		std::cout << "region : " << x.first << std::endl;
//	}
//	PAUSE;*/
//	auto elmToEdges = Mesh()->RetrieveElementToEdgesMap();
//	std::vector<std::shared_ptr<Element2d>> tris;
//	tris.reserve(elmToEdges.size());
//	for (const auto& x : elmToEdges)
//	{
//		auto elm_id = x.first;
//		const auto& currents = x.second;
//		if (currents.size() NOT_EQUAL 3)
//		{
//			FatalErrorIn(FunctionSIG)
//				<< "unsupported element type has been detected." << endl
//				<< " no. of points: " << currents.size() << endl
//				<< abort(FatalError);
//		}
//		auto edge0 = edges.at(Index_Of(currents.at(0)));
//		auto edge1 = edges.at(Index_Of(currents.at(1)));
//		auto edge2 = edges.at(Index_Of(currents.at(2)));
//
//		std::array<std::shared_ptr<Edge2d>, Element2d::nbEdges> t =
//		{ std::move(edge0),std::move(edge1),std::move(edge2) };
//		auto tri = std::make_shared<Element2d>(elm_id, std::move(t));
//		tris.push_back(std::move(tri));
//	}
//	for (const auto& x : all_edges)
//	{
//		auto owner = x.Owner();
//		auto neighbor = x.Neighbor();
//
//		auto edge = edges.at(Index_Of(x.Index()));
//		edge->SetOwner(tris.at(Index_Of(owner)));
//		if (neighbor) edge->SetNeighbor(tris.at(Index_Of(neighbor)));
//	}
//	/*k = 0;
//	for (const auto& x : theTris.Connectivity())
//	{
//		auto v0 = Index_Of(x.Value(0));
//		auto v1 = Index_Of(x.Value(1));
//		auto v2 = Index_Of(x.Value(2));
//
//		const auto& tri = tris.at(k++);
//
//		std::shared_ptr<Edge2d> edge0, edge1, edge2;
//		{
//			auto seg = RetrieveSegment(vertices.at(v0), vertices.at(v1));
//			auto sense = seg->ChackSense(vertices.at(v0), vertices.at(v1));
//			auto id = seg->Index();
//			edge0 = edges.at(Index_Of(id));
//			Debug_Null_Pointer(edge0);
//			sense ? edge0->SetOwner(tri) : edge0->SetNeighbor(tri);
//			if (NOT sense) edge0->SetSense(Standard_False);
//		}
//		{
//			auto seg = RetrieveSegment(vertices.at(v1), vertices.at(v2));
//			auto sense = seg->ChackSense(vertices.at(v1), vertices.at(v2));
//			auto id = seg->Index();
//			edge1 = edges.at(Index_Of(id));
//			Debug_Null_Pointer(edge1);
//			sense ? edge1->SetOwner(tri) : edge1->SetNeighbor(tri);
//			if (NOT sense) edge1->SetSense(Standard_False);
//		}
//		{
//			auto seg = RetrieveSegment(vertices.at(v2), vertices.at(v0));
//			auto sense = seg->ChackSense(vertices.at(v2), vertices.at(v0));
//			auto id = seg->Index();
//			edge2 = edges.at(Index_Of(id));
//			Debug_Null_Pointer(edge2);
//			sense ? edge2->SetOwner(tri) : edge2->SetNeighbor(tri);
//			if (NOT sense) edge2->SetSense(Standard_False);
//		}
//	}*/
//	auto t = std::make_tuple(std::move(tris), std::move(edges), std::move(nodes2d));
//	return std::move(t);
//}