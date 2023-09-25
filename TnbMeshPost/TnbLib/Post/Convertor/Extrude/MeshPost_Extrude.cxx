#include <Entity2d_CmpConnect.hxx>
#include <MeshPost_Extrude.hxx>

#include <MeshPost2d_OFTopology.hxx>
#include <MeshIO3d_PentaFEA.hxx>
#include <MeshIO2d_FEA.hxx>
#include <Geo3d_FVMesh.hxx>
#include <Geo_ElemGeom_Hexahedron.hxx>
#include <Geo_ElemGeom_Pyramid.hxx>
#include <Geo_ElemGeom_Quadrilateral.hxx>
#include <Geo_ElemGeom_Triangle.hxx>
#include <Entity2d_CmpMesh.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity2d_Triangulation.hxx>

std::vector<std::shared_ptr<tnbLib::MeshPost_Extrude::Node>>
tnbLib::MeshPost_Extrude::TriFacet::GetNodes() const
{
	std::vector<std::shared_ptr<Node>> nodes;
	std::copy(theNodes_.begin(), theNodes_.end(), std::back_inserter(nodes));
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::MeshPost_Extrude::Node>>
tnbLib::MeshPost_Extrude::QuadFacet::GetNodes() const
{
	std::vector<std::shared_ptr<Node>> nodes;
	std::copy(theNodes_.begin(), theNodes_.end(), std::back_inserter(nodes));
	return std::move(nodes);
}

//std::vector<std::shared_ptr<tnbLib::MeshPost_Extrude::Node>>
//tnbLib::MeshPost_Extrude::QuadFacet::GetNodes() const
//{
//	std::vector<std::shared_ptr<Node>> nodes;
//	std::copy(theNodes_.begin(), theNodes_.end(), std::back_inserter(nodes));
//	return std::move(nodes);
//}

std::vector<std::shared_ptr<tnbLib::MeshPost_Extrude::Node2d>>
tnbLib::MeshPost_Extrude::CalcNodes2d(const std::vector<std::shared_ptr<Node>>& theNodes)
{
	std::vector<std::shared_ptr<Node2d>> nodes;
	nodes.reserve(theNodes.size());
	for (const auto& x : theNodes)
	{
		if (auto master = std::dynamic_pointer_cast<MasterNode>(x))
		{
			auto node = std::make_shared<Node2d >(x->Index(), std::move(master));
			nodes.push_back(std::move(node));
		}
	}
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::MeshPost_Extrude::Node>>
tnbLib::MeshPost_Extrude::CalcNodes
(
	const std::vector<Pnt2d>& thePnts,
	const Standard_Real theExtrusion
)
{
	std::vector<std::shared_ptr<MeshPost_Extrude::Node>> nodes;
	nodes.reserve(thePnts.size() * 2);
	Standard_Integer k = 0;
	for (const auto& x : thePnts)
	{
		Pnt3d pt(x.X(), x.Y(), 0);
		auto node =
			std::make_shared<MeshPost_Extrude::MasterNode>
			(++k, std::move(pt));
		nodes.push_back(std::move(node));
	}
	std::vector<std::shared_ptr<MeshPost_Extrude::Node>> slaves;
	for (const auto& x : thePnts)
	{
		Pnt3d pt(x.X(), x.Y(), theExtrusion);
		auto node =
			std::make_shared<MeshPost_Extrude::SlaveNode>
			(++k, std::move(pt));
		slaves.push_back(std::move(node));
	}
	for (size_t i = 0; i < nodes.size(); i++)
	{
		std::dynamic_pointer_cast<MeshPost_Extrude::MasterNode>
			(nodes.at(i))->SlaveRef() =
			std::dynamic_pointer_cast<SlaveNode>(slaves.at(i));
	}
	for (auto& x : slaves)
	{
		nodes.push_back(std::move(x));
	}
	return std::move(nodes);
}

std::tuple
<
	std::vector<std::shared_ptr<tnbLib::MeshPost_Extrude::Element2d>>,
	std::vector<std::shared_ptr<tnbLib::MeshPost_Extrude::Edge2d>>,
	std::vector<std::shared_ptr<tnbLib::MeshPost_Extrude::Node2d>>
>
tnbLib::MeshPost_Extrude::CalcMesh2d
(
	const std::vector<std::shared_ptr<Node>>& theNodes
)
{
	auto nodes2d = CalcNodes2d(theNodes);
	/*for (const auto& x : nodes2d)
	{
		auto master = x->Node3d();
		std::cout << "master = " << master->Index() << ", slave = " << master->Slave()->Index() << std::endl;
	}
	PAUSE;*/
	if (NOT Mesh2d()->MeshIO())
	{
		FatalErrorIn(FunctionSIG)
			<< "no triangulation has been found." << endl
			<< abort(FatalError);
	}
	const auto& mesh = Mesh2d()->MeshIO()->Mesh();
	if (NOT mesh)
	{
		FatalErrorIn(FunctionSIG)
			<< "no triangulation has been found." << endl
			<< abort(FatalError);
	}
	const auto nbIteriors = Mesh2d()->Interiors().size();
	auto all_edges = Mesh2d()->RetrieveEdges();
	//const auto& int_edges = Mesh()->Interiors();
	//const auto& bnd_edges = Mesh()->RetrieveBoundaries();

	std::vector<std::shared_ptr<Edge2d>> edges;
	edges.reserve(all_edges.size());
	for (const auto& x : all_edges)
	{
		auto i0 = x.V0();
		auto i1 = x.V1();

		auto id = x.Index();
		std::array<std::shared_ptr<Node2d>, Edge2d::nbNodes> paired =
		{ nodes2d.at(Index_Of(i0)), nodes2d.at(Index_Of(i1)) };

		auto edge = std::make_shared<Edge2d>(id, std::move(paired));
		edges.push_back(std::move(edge));
	}
	/*for (const auto& x : Mesh()->Boundaries())
	{
		std::cout << "region : " << x.first << std::endl;
	}
	PAUSE;*/
	const auto cmp_mesh = Mesh2d()->MeshIO()->Mesh();
	Standard_Integer k = 0;
	std::vector<std::shared_ptr<Element2d>> elements;
	for (const auto& x : cmp_mesh->Indices())
	{
		auto ids = x->Components();
		if (x->IsTriangle())
		{
			const auto v0 = ids.at(0);
			const auto v1 = ids.at(1);
			const auto v2 = ids.at(2);

			k++;
			std::array<std::shared_ptr<Node2d>, TriElement2d::nbNodes> nodes =
			{ nodes2d.at(Index_Of(v0)), nodes2d.at(Index_Of(v1)), nodes2d.at(Index_Of(v2)) };

			auto elem = std::make_shared<TriElement2d>(k, std::move(nodes));
			elements.push_back(std::move(elem));
		}
		else if (x->IsQuadrilateral())
		{
			const auto v0 = ids.at(0);
			const auto v1 = ids.at(1);
			const auto v2 = ids.at(2);
			const auto v3 = ids.at(3);

			k++;
			std::array<std::shared_ptr<Node2d>, QuadElement2d::nbNodes> nodes =
			{ nodes2d.at(Index_Of(v0)), nodes2d.at(Index_Of(v1)), nodes2d.at(Index_Of(v2)), nodes2d.at(Index_Of(v3)) };

			auto elem = std::make_shared<QuadElement2d>(k, std::move(nodes));
			elements.push_back(std::move(elem));
		}
	}
	auto t = std::make_tuple(std::move(elements), std::move(edges), std::move(nodes2d));
	return std::move(t);
}

std::tuple
<
	std::shared_ptr<tnbLib::MeshPost_Extrude::Node2d>,
	std::shared_ptr<tnbLib::MeshPost_Extrude::Node2d>,
	std::shared_ptr<tnbLib::MeshPost_Extrude::Node2d>
> 
tnbLib::MeshPost_Extrude::RetrieveNodes(const TriElement2d& theElement)
{
	auto id = theElement.Index();
	const auto& nodes = theElement.Nodes();
	auto t = std::make_tuple(nodes.at(0), nodes.at(1), nodes.at(2));
	return std::move(t);
}

std::tuple<std::shared_ptr<tnbLib::MeshPost_Extrude::Node2d>, std::shared_ptr<tnbLib::MeshPost_Extrude::Node2d>, std::
shared_ptr<tnbLib::MeshPost_Extrude::Node2d>, std::shared_ptr<tnbLib::MeshPost_Extrude::Node2d>> tnbLib::
MeshPost_Extrude::RetrieveNodes(const QuadElement2d& theElement)
{
	auto id = theElement.Index();
	const auto& nodes = theElement.Nodes();
	auto t = std::make_tuple(nodes.at(0), nodes.at(1), nodes.at(2), nodes.at(3));
	return std::move(t);
}

void tnbLib::MeshPost_Extrude::CreateFace
(
	const std::shared_ptr<Element2d>& theElement,
	const Standard_Integer theIndex
)
{
	if (theElement->IsTriangle())
	{
		const auto element = std::dynamic_pointer_cast<TriElement2d>(theElement);
		Debug_Null_Pointer(element);
		auto [n0, n1, n2] = RetrieveNodes(*element);
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		Debug_Null_Pointer(n2);
		auto n0_f0 = n0->Node3d();
		auto n1_f0 = n1->Node3d();
		auto n2_f0 = n2->Node3d();
		Debug_Null_Pointer(n0_f0);
		Debug_Null_Pointer(n1_f0);
		Debug_Null_Pointer(n2_f0);

		auto n0_f1 = n0_f0->Slave();
		auto n1_f1 = n1_f0->Slave();
		auto n2_f1 = n2_f0->Slave();
		Debug_Null_Pointer(n0_f1);
		Debug_Null_Pointer(n1_f1);
		Debug_Null_Pointer(n2_f1);
		{
			std::array<std::shared_ptr<Node>, TriFacet::nbNodes> nodes =
			{ std::move(n0_f0), std::move(n1_f0), std::move(n2_f0) };
			auto f = std::make_shared<TriFacet>(theIndex + 1, std::move(nodes));
			element->FrontRef() = std::move(f);
		}
		{
			std::array<std::shared_ptr<Node>, TriFacet::nbNodes> nodes =
			{ std::move(n0_f1), std::move(n1_f1), std::move(n2_f1) };
			auto f = std::make_shared<TriFacet>(theIndex + 2, std::move(nodes));
			element->BackRef() = std::move(f);
		}
	}
	else if (theElement->IsQuadrilateral())
	{
		const auto element = std::dynamic_pointer_cast<QuadElement2d>(theElement);
		Debug_Null_Pointer(element);
		auto [n0, n1, n2, n3] = RetrieveNodes(*element);
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		Debug_Null_Pointer(n2);
		Debug_Null_Pointer(n3);
		auto n0_f0 = n0->Node3d();
		auto n1_f0 = n1->Node3d();
		auto n2_f0 = n2->Node3d();
		auto n3_f0 = n3->Node3d();
		Debug_Null_Pointer(n0_f0);
		Debug_Null_Pointer(n1_f0);
		Debug_Null_Pointer(n2_f0);
		Debug_Null_Pointer(n3_f0);

		auto n0_f1 = n0_f0->Slave();
		auto n1_f1 = n1_f0->Slave();
		auto n2_f1 = n2_f0->Slave();
		auto n3_f1 = n3_f0->Slave();
		Debug_Null_Pointer(n0_f1);
		Debug_Null_Pointer(n1_f1);
		Debug_Null_Pointer(n2_f1);
		Debug_Null_Pointer(n3_f1);
		{
			std::array<std::shared_ptr<Node>, QuadFacet::nbNodes> nodes =
			{ std::move(n0_f0), std::move(n1_f0), std::move(n2_f0), std::move(n3_f0) };
			auto f = std::make_shared<QuadFacet>(theIndex + 1, std::move(nodes));
			element->FrontRef() = std::move(f);
		}
		{
			std::array<std::shared_ptr<Node>, QuadFacet::nbNodes> nodes =
			{ std::move(n0_f1), std::move(n1_f1), std::move(n2_f1), std::move(n3_f1) };
			auto f = std::make_shared<QuadFacet>(theIndex + 2, std::move(nodes));
			element->BackRef() = std::move(f);
		}
	}
	else
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Unspecified type of element." << endl
			<< abort(FatalError);
	}
	
}

void tnbLib::MeshPost_Extrude::CalcFaces
(
	const std::vector<std::shared_ptr<Element2d>>& theElements,
	const Standard_Integer theNbEdges
)
{
	auto nf = theNbEdges;
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		CreateFace(x, nf);

		nf = nf + 2;
	}
}

void tnbLib::MeshPost_Extrude::CalcElements
(
	const std::vector<std::shared_ptr<Element2d>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		if (x->IsTriangle())
		{
			const auto tri_elm = std::dynamic_pointer_cast<TriElement2d>(x);
			Debug_Null_Pointer(elm);
			const auto f0 = tri_elm->Front();
			const auto f1 = tri_elm->Back();
			Debug_Null_Pointer(f0);
			Debug_Null_Pointer(f1);
			std::array<std::shared_ptr<Node>, PrismElement::nbNodes>
				nodes =
			{ f0->Nodes().at(0), f0->Nodes().at(1), f0->Nodes().at(2),
				f1->Nodes().at(0), f1->Nodes().at(1), f1->Nodes().at(2) };
			//std::cout << nodes.at(0)->Index() << ", " << nodes.at(1)->Index() << ", " << nodes.at(2)->Index() << ", " << nodes.at(3)->Index() << ", " << nodes.at(4)->Index() << ", " << nodes.at(5)->Index() << std::endl;
			auto elm = std::make_shared<PrismElement>(x->Index(), std::move(nodes));
			tri_elm->GetElement3dRef() = std::move(elm);
		}
		else if (x->IsQuadrilateral())
		{
			const auto q_elm = std::dynamic_pointer_cast<QuadElement2d>(x);
			Debug_Null_Pointer(elm);
			const auto f0 = q_elm->Front();
			const auto f1 = q_elm->Back();
			Debug_Null_Pointer(f0);
			Debug_Null_Pointer(f1);
			std::array<std::shared_ptr<Node>, HexaElement::nbNodes>
				nodes =
			{ f0->Nodes().at(0), f0->Nodes().at(1), f0->Nodes().at(2), f0->Nodes().at(3),
				f1->Nodes().at(0), f1->Nodes().at(1), f1->Nodes().at(2), f1->Nodes().at(3) };
			//std::cout << nodes.at(0)->Index() << ", " << nodes.at(1)->Index() << ", " << nodes.at(2)->Index() << ", " << nodes.at(3)->Index() << ", " << nodes.at(4)->Index() << ", " << nodes.at(5)->Index() << std::endl;
			auto elm = std::make_shared<HexaElement>(x->Index(), std::move(nodes));
			q_elm->GetElement3dRef() = std::move(elm);
		}
		else
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Unspecified type of element." << endl
				<< abort(FatalError);
		}
		
	}
}

tnbLib::MeshPost_Extrude::PointList
tnbLib::MeshPost_Extrude::RetrievePointList
(
	const std::vector<std::shared_ptr<Node>>& theNodes
)
{
	std::vector<Pnt3d> coords;
	coords.reserve(theNodes.size());
	for (const auto& x : theNodes)
	{
		coords.push_back(x->Coord());
	}
	PointList pointList(std::move(coords));
	return std::move(pointList);
}

tnbLib::MeshPost_Extrude::CellList
tnbLib::MeshPost_Extrude::RetrieveCellList
(
	const std::vector<std::shared_ptr<Element2d>>& theElements
)
{
	std::vector<std::shared_ptr<Cell>> cells;
	cells.reserve(theElements.size());
	for (const auto& x : theElements)
	{
		auto c = RetrieveCell(x);
		cells.push_back(std::move(c));
	}
	CellList cellList(std::move(cells));
	return std::move(cellList);
}

std::shared_ptr<tnbLib::MeshPost_Extrude::Cell>
tnbLib::MeshPost_Extrude::RetrieveCell(const std::shared_ptr<Element2d>& theElement)
{
	if (theElement->IsTriangle())
	{
		auto elm2d = std::dynamic_pointer_cast<TriElement2d>(theElement);
		Debug_Null_Pointer(elm2d);
		std::array<Standard_Integer, PrismCell::nbNodes> nodes;
		const auto elm = std::dynamic_pointer_cast<PrismElement>(elm2d->GetElement3d());
		Debug_Null_Pointer(elm);
		nodes.at(0) = elm->Nodes().at(0)->Index();
		nodes.at(1) = elm->Nodes().at(1)->Index();
		nodes.at(2) = elm->Nodes().at(2)->Index();
		nodes.at(3) = elm->Nodes().at(3)->Index();
		nodes.at(4) = elm->Nodes().at(4)->Index();
		nodes.at(5) = elm->Nodes().at(5)->Index();
		auto cell = std::make_shared<PrismCell>(std::move(nodes));
		return std::move(cell);
	}
	else if (theElement->IsQuadrilateral())
	{
		auto elm2d = std::dynamic_pointer_cast<QuadElement2d>(theElement);
		Debug_Null_Pointer(elm2d);
		std::array<Standard_Integer, HexaCell::nbNodes> nodes;
		const auto elm = std::dynamic_pointer_cast<HexaElement>(elm2d->GetElement3d());
		Debug_Null_Pointer(elm);
		nodes.at(0) = elm->Nodes().at(0)->Index();
		nodes.at(1) = elm->Nodes().at(1)->Index();
		nodes.at(2) = elm->Nodes().at(2)->Index();
		nodes.at(3) = elm->Nodes().at(3)->Index();
		nodes.at(4) = elm->Nodes().at(4)->Index();
		nodes.at(5) = elm->Nodes().at(5)->Index();
		nodes.at(6) = elm->Nodes().at(6)->Index();
		nodes.at(7) = elm->Nodes().at(7)->Index();
		auto cell = std::make_shared<HexaCell>(std::move(nodes));
		return std::move(cell);
	}
	else
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Unspecified type of element." << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Geo3d_FVMesh> 
tnbLib::MeshPost_Extrude::RetrieveIO() const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the application is not performed." << endl
			<< abort(FatalError);
	}
	std::vector<Pnt3d> coords = thePoints_.Coords();
	std::vector<std::shared_ptr<Geo_ElemGeom>> elements;
	elements.reserve(theCells_.Cells().size());
	for (const auto& x : theCells_.Cells())
	{
		if (x->IsPrism())
		{
			const auto cell = std::dynamic_pointer_cast<PrismCell>(x);
			Debug_Null_Pointer(cell);
			const auto& nodes = cell->Nodes();
			std::vector<Standard_Integer> indices;
			std::copy(nodes.begin(), nodes.end(), std::back_inserter(indices));
			const auto v0 = indices.at(0);
			const auto v1 = indices.at(1);
			const auto v2 = indices.at(2);
			const auto v3 = indices.at(3);
			const auto v4 = indices.at(4);
			const auto v5 = indices.at(5);
			std::array<Standard_Integer, Geo_ElemGeom_Pyramid::nbNodes>
				indices_array = { v0,v1,v2,v3,v4,v5 };
			auto elm = std::make_shared<Geo_ElemGeom_Pyramid>(std::move(indices_array));
			elements.push_back(std::move(elm));
		}
		else if (x->IsHexa())
		{
			const auto cell = std::dynamic_pointer_cast<HexaCell>(x);
			Debug_Null_Pointer(cell);
			const auto& nodes = cell->Nodes();
			std::vector<Standard_Integer> indices;
			std::copy(nodes.begin(), nodes.end(), std::back_inserter(indices));
			const auto v0 = indices.at(0);
			const auto v1 = indices.at(1);
			const auto v2 = indices.at(2);
			const auto v3 = indices.at(3);
			const auto v4 = indices.at(4);
			const auto v5 = indices.at(5);
			const auto v6 = indices.at(6);
			const auto v7 = indices.at(7);
			std::array<Standard_Integer, Geo_ElemGeom_Hexahedron::nbNodes>
				indices_array = { v0,v1,v2,v3,v4,v5,v6,v7 };
			auto elm = std::make_shared<Geo_ElemGeom_Hexahedron>(std::move(indices_array));
			elements.push_back(std::move(elm));
		}
		else
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Unspecified type of element." << endl
				<< abort(FatalError);
		}
		
	}
	std::vector<std::shared_ptr<Geo3d_FVMesh::Boundary>> boundaries;
	for (const auto& x : theBoundaryConditions_)
	{
		std::vector<std::shared_ptr<Geo_ElemGeom>> faces;
		for (const auto& f : x.second)
		{
			const auto& nodes = f.Nodes();
			if (nodes.size() IS_EQUAL 3)
			{
				const auto v0 = nodes.at(0);
				const auto v1 = nodes.at(1);
				const auto v2 = nodes.at(2);
				std::array<Standard_Integer, Geo_ElemGeom_Triangle::nbNodes>
					indices_array = { v0, v1,v2 };
				auto elm = std::make_shared<Geo_ElemGeom_Triangle>(std::move(indices_array));
				faces.push_back(std::move(elm));
			}
			else if (nodes.size() IS_EQUAL 4)
			{
				const auto v0 = nodes.at(0);
				const auto v1 = nodes.at(1);
				const auto v2 = nodes.at(2);
				const auto v3 = nodes.at(3);
				std::array<Standard_Integer, Geo_ElemGeom_Quadrilateral::nbNodes>
					indices_array = { v0, v1,v2,v3 };
				auto elm = std::make_shared<Geo_ElemGeom_Quadrilateral>(std::move(indices_array));
				faces.push_back(std::move(elm));
			}
			else
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "unspecified type of element has been detected." << endl
					<< abort(FatalError);
			}
			
		}
		auto bnd = std::make_shared<Geo3d_FVMesh::Boundary>(x.first, std::move(faces));
		boundaries.push_back(std::move(bnd));
	}

	auto meshIO = std::make_shared<Geo3d_FVMesh>
		(Title(), std::move(coords), std::move(elements), std::move(boundaries));
	return std::move(meshIO);
}

void tnbLib::MeshPost_Extrude::Perform()
{
	if (NOT Mesh2d())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh has been found." << endl
			<< abort(FatalError);
	}
	const auto& meshIO = Mesh2d()->MeshIO();
	if (NOT meshIO)
	{
		FatalErrorIn(FunctionSIG)
			<< "no io structure has been found." << endl
			<< abort(FatalError);
	}
	const auto& mesh = meshIO->Mesh();
	if (NOT mesh)
	{
		FatalErrorIn(FunctionSIG)
			<< "no triangulation has been found." << endl
			<< abort(FatalError);
	}
	theExtrusion_ = 0.1;

	const auto nodes = CalcNodes(mesh->Coords(), Extrusion());

	auto [elements_2d, edges_2d, nodes_2d] =
		CalcMesh2d(nodes);

	CalcFaces(elements_2d, (Standard_Integer)edges_2d.size());

	CalcElements(elements_2d);

	thePoints_ = RetrievePointList(nodes);
	theCells_ = RetrieveCellList(elements_2d);

	Standard_Integer k = 0;
	for (const auto& x : Mesh2d()->Boundaries())
	{
		const auto& bnd = x.first;
		auto iter = theBoundaryConditions_.find(bnd);
		if (iter IS_EQUAL theBoundaryConditions_.end())
		{
			auto paired = std::make_pair(bnd, std::vector<Face>());
			theBoundaryConditions_.insert(std::move(paired));
		}
		auto& faces = theBoundaryConditions_.at(bnd);
		const auto& edges = x.second;

		for (const auto& edge : edges)
		{
			auto v0 = edge.V0();
			auto v1 = edge.V1();
			std::cout << " - " << bnd << ", " << edge.Index() << std::endl;
			const auto& n0 = nodes_2d.at(Index_Of(v0));
			const auto& n1 = nodes_2d.at(Index_Of(v1));

			Debug_Null_Pointer(n0->Node3d());
			Debug_Null_Pointer(n1->Node3d());
			const auto& s0 = n0->Node3d()->Slave();
			const auto& s1 = n1->Node3d()->Slave();
			Debug_Null_Pointer(s0);
			Debug_Null_Pointer(s1);

			std::vector<Standard_Integer> face =
			{ v0,v1,s1->Index(),s0->Index() };
			faces.push_back(std::move(face));
		}
	}
	theBoundaryConditions_.insert({ "frontAndBack", std::vector<Face>() });
	{
		auto& faces = theBoundaryConditions_.at("frontAndBack");
		for (const auto& elm : elements_2d)
		{
			if (elm->IsTriangle())
			{
				auto tri = std::dynamic_pointer_cast<TriElement2d>(elm);
				Debug_Null_Pointer(tri);
				const auto& front = tri->Front();
				Debug_Null_Pointer(front);
				const auto& nodes = front->Nodes();
				std::vector<Standard_Integer> indices;
				for (const auto& n : nodes) indices.push_back(n->Index());
				std::reverse(indices.begin(), indices.end());
				faces.push_back({ std::move(indices) });
			}
			else if (elm->IsQuadrilateral())
			{
				auto quad = std::dynamic_pointer_cast<QuadElement2d>(elm);
				Debug_Null_Pointer(quad);
				const auto& front = quad->Front();
				Debug_Null_Pointer(front);
				const auto& nodes = front->Nodes();
				std::vector<Standard_Integer> indices;
				for (const auto& n : nodes) indices.push_back(n->Index());
				std::reverse(indices.begin(), indices.end());
				faces.push_back({ std::move(indices) });
			}
			else
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "unspecified type of element has been detected." << endl
					<< abort(FatalError);
			}
			
		}
		for (const auto& elm : elements_2d)
		{
			if (elm->IsTriangle())
			{
				auto tri = std::dynamic_pointer_cast<TriElement2d>(elm);
				Debug_Null_Pointer(tri);
				const auto& back = tri->Back();
				Debug_Null_Pointer(back);
				const auto& nodes = back->Nodes();
				std::vector<Standard_Integer> indices;
				for (const auto& n : nodes) indices.push_back(n->Index());
				faces.push_back({ std::move(indices) });
			}
			else if (elm->IsQuadrilateral())
			{
				auto quad = std::dynamic_pointer_cast<QuadElement2d>(elm);
				Debug_Null_Pointer(quad);
				const auto& back = quad->Back();
				Debug_Null_Pointer(back);
				const auto& nodes = back->Nodes();
				std::vector<Standard_Integer> indices;
				for (const auto& n : nodes) indices.push_back(n->Index());
				faces.push_back({ std::move(indices) });
			}
			else
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "unspecified type of element has been detected." << endl
					<< abort(FatalError);
			}
			
		}
	}
	Change_IsDone() = Standard_True;
}