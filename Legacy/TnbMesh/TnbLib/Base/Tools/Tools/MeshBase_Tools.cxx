#include <MeshBase_Tools.hxx>

#include <Mesh_SetSourcesNode.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_Node.hxx>
#include <Mesh2d_Element.hxx>
#include <Pln_Curve.hxx>
#include <TModel_ParaCurve.hxx>
#include <GModel_ParaCurve.hxx>
#include <GeoMesh2d_Background.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_TetrahedralizationTools.hxx>
#include <Entity2d_MeshValue.hxx>
#include <Entity2d_MetricMeshValue.hxx>
#include <Entity2d_Metric1.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/Geom2d_Curve.hxx>

#include <armadillo>

using namespace arma;

std::tuple<Standard_Integer, Standard_Integer>
tnbLib::MeshBase_Tools::Ids(const Mesh2d_Edge & theEdge)
{
	Debug_Null_Pointer(theEdge.Node0());
	Debug_Null_Pointer(theEdge.Node1());

	auto t = std::make_tuple(theEdge.Node0()->Index(), theEdge.Node1()->Index());
	return std::move(t);
}

std::tuple<Standard_Integer, Standard_Integer, Standard_Integer> 
tnbLib::MeshBase_Tools::Ids
(
	const Mesh2d_Element & theElement
)
{
	Debug_Null_Pointer(theElement.Node0());
	Debug_Null_Pointer(theElement.Node1());
	Debug_Null_Pointer(theElement.Node2());

	auto t = 
		std::make_tuple
		(
			theElement.Node0()->Index(), 
			theElement.Node1()->Index(), 
			theElement.Node2()->Index()
		);
	return std::move(t);
}

std::tuple<Standard_Integer, Standard_Integer> 
tnbLib::MeshBase_Tools::Ids(const Mesh3d_Edge & theEdge)
{
	Debug_Null_Pointer(theEdge.Node0());
	Debug_Null_Pointer(theEdge.Node1());

	auto t = std::make_tuple(theEdge.Node0()->Index(), theEdge.Node1()->Index());
	return std::move(t);
}

std::tuple<Standard_Integer, Standard_Integer, Standard_Integer> 
tnbLib::MeshBase_Tools::Ids
(
	const Mesh3d_Facet & theElement
)
{
	Debug_Null_Pointer(theElement.Node0());
	Debug_Null_Pointer(theElement.Node1());
	Debug_Null_Pointer(theElement.Node2());

	auto t =
		std::make_tuple
		(
			theElement.Node0()->Index(),
			theElement.Node1()->Index(),
			theElement.Node2()->Index()
		);
	return std::move(t);
}

std::tuple<Standard_Integer, Standard_Integer, Standard_Integer, Standard_Integer> 
tnbLib::MeshBase_Tools::Ids(const Mesh3d_Element & theElement)
{
	Debug_Null_Pointer(theElement.Node0());
	Debug_Null_Pointer(theElement.Node1());
	Debug_Null_Pointer(theElement.Node2());
	Debug_Null_Pointer(theElement.Node3());

	auto t =
		std::make_tuple
		(
			theElement.Node0()->Index(),
			theElement.Node1()->Index(),
			theElement.Node2()->Index(),
			theElement.Node3()->Index()
		);
	return std::move(t);
}

std::tuple
<
	tnbLib::connectivity::triple,
	tnbLib::connectivity::triple,
	tnbLib::connectivity::triple, 
	tnbLib::connectivity::triple
> 
tnbLib::MeshBase_Tools::FaceIds
(
	const Mesh3d_Element & theElement
)
{
	static auto makeTriple = [](const Standard_Integer i0, const Standard_Integer i1, const Standard_Integer i2)
	{
		connectivity::triple t;
		t.Value(0) = i0;
		t.Value(1) = i1;
		t.Value(2) = i2;
		return std::move(t);
	};

	connectivity::triple f0;
	{
		auto Id = Entity3d_TetrahedralizationTools::FacetIndices(0);

		const auto& node1 = theElement.Node(Index_Of(std::get<0>(Id)));
		const auto& node2 = theElement.Node(Index_Of(std::get<1>(Id)));
		const auto& node3 = theElement.Node(Index_Of(std::get<2>(Id)));

		Debug_Null_Pointer(node1);
		Debug_Null_Pointer(node2);
		Debug_Null_Pointer(node3);
		f0 = makeTriple(node1->Index(), node2->Index(), node3->Index());
	}
	connectivity::triple f1;
	{
		auto Id = Entity3d_TetrahedralizationTools::FacetIndices(1);

		const auto& node1 = theElement.Node(Index_Of(std::get<0>(Id)));
		const auto& node2 = theElement.Node(Index_Of(std::get<1>(Id)));
		const auto& node3 = theElement.Node(Index_Of(std::get<2>(Id)));

		Debug_Null_Pointer(node1);
		Debug_Null_Pointer(node2);
		Debug_Null_Pointer(node3);
		f1 = makeTriple(node1->Index(), node2->Index(), node3->Index());
	}
	connectivity::triple f2;
	{
		auto Id = Entity3d_TetrahedralizationTools::FacetIndices(2);

		const auto& node1 = theElement.Node(Index_Of(std::get<0>(Id)));
		const auto& node2 = theElement.Node(Index_Of(std::get<1>(Id)));
		const auto& node3 = theElement.Node(Index_Of(std::get<2>(Id)));

		Debug_Null_Pointer(node1);
		Debug_Null_Pointer(node2);
		Debug_Null_Pointer(node3);
		f2 = makeTriple(node1->Index(), node2->Index(), node3->Index());
	}
	connectivity::triple f3;
	{
		auto Id = Entity3d_TetrahedralizationTools::FacetIndices(3);

		const auto& node1 = theElement.Node(Index_Of(std::get<0>(Id)));
		const auto& node2 = theElement.Node(Index_Of(std::get<1>(Id)));
		const auto& node3 = theElement.Node(Index_Of(std::get<2>(Id)));

		Debug_Null_Pointer(node1);
		Debug_Null_Pointer(node2);
		Debug_Null_Pointer(node3);
		f3 = makeTriple(node1->Index(), node2->Index(), node3->Index());
	}
	auto t = std::make_tuple(std::move(f0), std::move(f1), std::move(f2), std::move(f3));
	return std::move(t);
}

std::shared_ptr<tnbLib::Entity2d_Box> 
tnbLib::MeshBase_Tools::CalcBoundingBox
(
	const std::shared_ptr<Mesh2d_Element>& theElement
)
{
	Debug_Null_Pointer(theElement);
	const auto[p0, p1, p2] = theElement->RetrieveCoords();
	auto t = Geo_BoxTools::GeoBox(p0, p1, p2);
	return std::move(t);
}

std::shared_ptr<tnbLib::Entity3d_Box>
tnbLib::MeshBase_Tools::CalcBoundingBox
(
	const std::shared_ptr<Mesh3d_Element>& theElement
)
{
	Debug_Null_Pointer(theElement);
	const auto[p0, p1, p2, p3] = theElement->RetrieveCoords();
	auto t = Geo_BoxTools::GetBox(p0, p1, p2, p3);
	return std::move(t);
}

tnbLib::Pnt2d 
tnbLib::MeshBase_Tools::CalcAnalyCoord
(
	const Pnt2d & theP0,
	const Pnt2d & theP1, 
	const Pnt2d & theCentre, 
	const Entity2d_Metric1 & m0, 
	const Standard_Real h,
	const Standard_Real len
)
{
	static const Standard_Real c3 = 0.86602540378443864676372317075294;
	const auto invH2 = (Standard_Real)1.0 / (h * h);

	Entity2d_Metric1 m(invH2*m0.A(), invH2*m0.B(), invH2*m0.C());
	const auto D = std::sqrt(m.Determinant());
	const auto cte = c3 / (D * len);

	auto dU = theP1 - theCentre;

	vec2 U;
	U(0) = dU.X();
	U(1) = dU.Y();

	mat22 orthM;
	orthM(0, 0) = -m.B();
	orthM(0, 1) = -m.C();
	orthM(1, 0) = m.A();
	orthM(1, 1) = m.B();

	U = cte * (orthM * U);

	Pnt2d P(theCentre.X() + U(0), theCentre.Y() + U(1));
	return std::move(P);
}

namespace tnbLib
{

	namespace meshLib
	{

		static std::shared_ptr<Mesh3d_Node> 
			RetrieveClosestNode
			(
				const std::tuple
				<
				std::shared_ptr<Mesh3d_Node>, 
				std::shared_ptr<Mesh3d_Node>, 
				std::shared_ptr<Mesh3d_Node>,
				std::shared_ptr<Mesh3d_Node>
				>& theNodes,
				const Pnt3d& theCoord
			)
		{
			auto[n0, n1, n2, n3] = theNodes;
			Standard_Real dis = theCoord.SquareDistance(n0->Coord());
			auto nearest = std::move(n0);
			
			const auto d1 = theCoord.SquareDistance(n1->Coord());
			if (d1 < dis)
			{
				dis = d1;
				nearest = std::move(n1);
			}
			const auto d2 = theCoord.SquareDistance(n2->Coord());
			if (d2 < dis)
			{
				dis = d2;
				nearest = std::move(n2);
			}
			const auto d3 = theCoord.SquareDistance(n3->Coord());
			if (d3 < dis)
			{
				dis = d3;
				nearest = std::move(n3);
			}
			return std::move(nearest);
		}

		static std::shared_ptr<Mesh2d_Node>
			RetrieveClosestNode
			(
				const std::tuple
				<
				std::shared_ptr<Mesh2d_Node>,
				std::shared_ptr<Mesh2d_Node>,
				std::shared_ptr<Mesh2d_Node>
				>& theNodes,
				const Pnt2d& theCoord
			)
		{
			auto [n0, n1, n2] = theNodes;
			Standard_Real dis = theCoord.SquareDistance(n0->Coord());
			auto nearest = std::move(n0);

			const auto d1 = theCoord.SquareDistance(n1->Coord());
			if (d1 < dis)
			{
				dis = d1;
				nearest = std::move(n1);
			}
			const auto d2 = theCoord.SquareDistance(n2->Coord());
			if (d2 < dis)
			{
				dis = d2;
				nearest = std::move(n2);
			}
			return std::move(nearest);
		}
	}
}

void tnbLib::MeshBase_Tools::SetSourcesToMeshNearestPoint
(
	const std::vector<std::shared_ptr<Mesh_SetSourcesNode<Pnt2d, Standard_Real>>>& theSources,
	const Standard_Real theBase,
	const Standard_Real theGrowthRate,
	GeoMesh2d_SingleBackground& theMesh
)
{
	const auto& mesh = *theMesh.Mesh();
	if (mesh.Elements().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the element list of the background mesh is empty!" << endl
			<< abort(FatalError);
	}

	auto meshNodes = RetrieveNodes(mesh.Elements());
	auto& sources = theMesh.Sources();
	sources.resize(meshNodes.size(), theBase);

	auto start = mesh.Elements().at(0);
	for (const auto& x : theSources)
	{
		const auto current = mesh.TriangleLocation(start, x->Coord());
		if (NOT current)
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the mesh!" << endl
				<< " - domain's of the mesh: " << theMesh.BoundingBox() << endl
				<< " - coordinates of the point: " << x->Coord() << endl
				<< abort(FatalError);
		}
		start = current;
		auto nodes = current->Nodes();
		auto nearest = meshLib::RetrieveClosestNode(nodes, x->Coord());
		auto neighbors = RetrieveAdjacentNodes(nearest);

		auto ho = sources.at(Index_Of(nearest->Index()));
		for (const auto& ni : neighbors)
		{
			Debug_Null_Pointer(ni);
			auto id = Index_Of(ni->Index());

			auto dx = nearest->Coord().Distance(ni->Coord());
			auto val = std::min(theBase, ho + theGrowthRate * dx);
			if (val < ho) sources.at(id) = val;
		}
		{
			auto id = Index_Of(nearest->Index());

			auto h = sources.at(id);
			if (x->H() < h) sources.at(id) = x->H();
		}
	}
}

void tnbLib::MeshBase_Tools::SetSourcesToMeshNearestPoint
(
	const std::vector<std::shared_ptr<Mesh_SetSourcesNode<Pnt3d, Standard_Real>>>& theSources,
	const Standard_Real theBase,
	const Standard_Real theGrowthRate,
	GeoMesh3d_SingleBackground& theMesh
)
{
	const auto& mesh = *theMesh.Mesh();
	if (mesh.Elements().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the element list of the background mesh is empty!" << endl
			<< abort(FatalError);
	}

	auto meshNodes = RetrieveNodes(mesh.Elements());
	auto& sources = theMesh.Sources();
	sources.resize(meshNodes.size(), theBase);

	auto start = mesh.Elements().at(0);
	for (const auto& x : theSources)
	{
		const auto current = mesh.TriangleLocation(start, x->Coord());
		if (NOT current)
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the mesh!" << endl
				<< " - domain's of the mesh: " << theMesh.BoundingBox() << endl
				<< " - coordinates of the point: " << x->Coord() << endl
				<< abort(FatalError);
		}
		start = current;

		auto nodes = current->Nodes();
		auto nearest = meshLib::RetrieveClosestNode(nodes, x->Coord());
		auto neighbors = RetrieveAdjacentNodes(nearest);

		auto ho = sources.at(Index_Of(nearest->Index()));
		for (const auto& ni : neighbors)
		{
			Debug_Null_Pointer(ni);
			auto id = Index_Of(ni->Index());

			auto dx = nearest->Coord().Distance(ni->Coord());
			auto val = std::min(theBase, ho + theGrowthRate * dx);
			if (val < ho) sources.at(id) = val;
		}
		{
			auto id = Index_Of(nearest->Index());

			auto h = sources.at(id);
			if (x->H() < h) sources.at(id) = x->H();
		}
	}
}

void tnbLib::MeshBase_Tools::SetSourcesToMesh
(
	const std::vector<std::shared_ptr<Mesh_SetSourcesNode<Pnt3d, Standard_Real>>>& theSources,
	const Standard_Real theBase,
	const Standard_Real theGrowthRate,
	GeoMesh3d_SingleBackground & theMesh
)
{
	const auto& mesh = *theMesh.Mesh();
	if (mesh.Elements().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the element list of the background mesh is empty!" << endl
			<< abort(FatalError);
	}

	auto meshNodes = RetrieveNodes(mesh.Elements());
	auto& sources = theMesh.Sources();
	sources.resize(meshNodes.size(), theBase);

	auto start = mesh.Elements().at(0);
	for (const auto& x : theSources)
	{
		const auto current = mesh.TriangleLocation(start, x->Coord());
		if (NOT current)
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the mesh!" << endl
				<< " - domain's of the mesh: " << theMesh.BoundingBox() << endl
				<< " - coordinates of the point: " << x->Coord() << endl
				<< abort(FatalError);
		}
		start = current;

		auto[n0, n1, n2, n3] = current->Nodes();
		{
			auto nearest = n0;
			auto neighbors = RetrieveAdjacentNodes(nearest);

			auto ho = sources.at(Index_Of(nearest->Index()));
			for (const auto& ni : neighbors)
			{
				Debug_Null_Pointer(ni);
				auto id = Index_Of(ni->Index());

				auto dx = nearest->Coord().Distance(ni->Coord());
				auto val = std::min(theBase, ho + theGrowthRate * dx);
				if (val < ho) sources.at(id) = val;
			}
			{
				auto id = Index_Of(nearest->Index());

				auto h = sources.at(id);
				if (x->H() < h) sources.at(id) = x->H();
			}
		}
		{
			auto nearest = n1;
			auto neighbors = RetrieveAdjacentNodes(nearest);

			auto ho = sources.at(Index_Of(nearest->Index()));
			for (const auto& ni : neighbors)
			{
				Debug_Null_Pointer(ni);
				auto id = Index_Of(ni->Index());

				auto dx = nearest->Coord().Distance(ni->Coord());
				auto val = std::min(theBase, ho + theGrowthRate * dx);
				if (val < ho) sources.at(id) = val;
			}
			{
				auto id = Index_Of(nearest->Index());

				auto h = sources.at(id);
				if (x->H() < h) sources.at(id) = x->H();
			}
		}
		{
			auto nearest = n2;
			auto neighbors = RetrieveAdjacentNodes(nearest);

			auto ho = sources.at(Index_Of(nearest->Index()));
			for (const auto& ni : neighbors)
			{
				Debug_Null_Pointer(ni);
				auto id = Index_Of(ni->Index());

				auto dx = nearest->Coord().Distance(ni->Coord());
				auto val = std::min(theBase, ho + theGrowthRate * dx);
				if (val < ho) sources.at(id) = val;
			}
			{
				auto id = Index_Of(nearest->Index());

				auto h = sources.at(id);
				if (x->H() < h) sources.at(id) = x->H();
			}
		}
		{
			auto nearest = n3;
			auto neighbors = RetrieveAdjacentNodes(nearest);

			auto ho = sources.at(Index_Of(nearest->Index()));
			for (const auto& ni : neighbors)
			{
				Debug_Null_Pointer(ni);
				auto id = Index_Of(ni->Index());

				auto dx = nearest->Coord().Distance(ni->Coord());
				auto val = std::min(theBase, ho + theGrowthRate * dx);
				if (val < ho) sources.at(id) = val;
			}
			{
				auto id = Index_Of(nearest->Index());

				auto h = sources.at(id);
				if (x->H() < h) sources.at(id) = x->H();
			}
		}
	}
}

void tnbLib::MeshBase_Tools::SetSourcesToMesh
(
	const std::vector<std::pair<Pnt2d, Standard_Real>>& theSources, 
	const Standard_Real theBaseSize, 
	GeoMesh2d_SingleBackground & theMesh
)
{
	const auto& mesh = *theMesh.Mesh();
	if (mesh.Elements().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the element list of the background mesh is empty!" << endl
			<< abort(FatalError);
	}

	auto& sources = theMesh.Sources();
	sources.resize(theSources.size(), theBaseSize);

	auto start = mesh.Elements().at(0);
	for (const auto& x : theSources)
	{
		const auto current = mesh.TriangleLocation(start, x.first);
		if (NOT current)
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the mesh!" << endl
				<< " - domain's of the mesh: " << theMesh.BoundingBox() << endl
				<< " - coordinates of the point: " << x.first << endl
				<< abort(FatalError);
		}
		start = current;

		const auto& currentRef = *current;
		auto n0 = Index_Of(currentRef.Node0()->Index());
		auto n1 = Index_Of(currentRef.Node1()->Index());
		auto n2 = Index_Of(currentRef.Node2()->Index());

		auto v0 = sources[n0];
		auto v1 = sources[n1];
		auto v2 = sources[n2];

		if (v0 < x.second) sources[n0] = v0;
		if (v1 < x.second) sources[n1] = v1;
		if (v2 < x.second) sources[n2] = v2;
	}
}

void tnbLib::MeshBase_Tools::SetSourcesToMesh
(
	const std::vector<std::shared_ptr<Mesh_SetSourcesNode<Pnt2d, Standard_Real>>>& theSources,
	const Standard_Real theBase, 
	const Standard_Real theGrowthRate, 
	GeoMesh2d_SingleBackground& theMesh
)
{
	const auto& mesh = *theMesh.Mesh();
	if (mesh.Elements().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the element list of the background mesh is empty!" << endl
			<< abort(FatalError);
	}

	auto meshNodes = RetrieveNodes(mesh.Elements());
	auto& sources = theMesh.Sources();
	sources.resize(meshNodes.size(), theBase);

	auto start = mesh.Elements().at(0);
	for (const auto& x : theSources)
	{
		const auto current = mesh.TriangleLocation(start, x->Coord());
		if (NOT current)
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the mesh!" << endl
				<< " - domain's of the mesh: " << theMesh.BoundingBox() << endl
				<< " - coordinates of the point: " << x->Coord() << endl
				<< abort(FatalError);
		}
		start = current;

		auto [n0, n1, n2] = current->Nodes();
		{
			auto nearest = n0;
			auto neighbors = RetrieveAdjacentNodes(nearest);

			auto ho = sources.at(Index_Of(nearest->Index()));
			for (const auto& ni : neighbors)
			{
				Debug_Null_Pointer(ni);
				auto id = Index_Of(ni->Index());

				auto dx = nearest->Coord().Distance(ni->Coord());
				auto val = std::min(theBase, ho + theGrowthRate * dx);
				if (val < ho) sources.at(id) = val;
			}
			{
				auto id = Index_Of(nearest->Index());

				auto h = sources.at(id);
				if (x->H() < h) sources.at(id) = x->H();
			}
		}
		{
			auto nearest = n1;
			auto neighbors = RetrieveAdjacentNodes(nearest);

			auto ho = sources.at(Index_Of(nearest->Index()));
			for (const auto& ni : neighbors)
			{
				Debug_Null_Pointer(ni);
				auto id = Index_Of(ni->Index());

				auto dx = nearest->Coord().Distance(ni->Coord());
				auto val = std::min(theBase, ho + theGrowthRate * dx);
				if (val < ho) sources.at(id) = val;
			}
			{
				auto id = Index_Of(nearest->Index());

				auto h = sources.at(id);
				if (x->H() < h) sources.at(id) = x->H();
			}
		}
		{
			auto nearest = n2;
			auto neighbors = RetrieveAdjacentNodes(nearest);

			auto ho = sources.at(Index_Of(nearest->Index()));
			for (const auto& ni : neighbors)
			{
				Debug_Null_Pointer(ni);
				auto id = Index_Of(ni->Index());

				auto dx = nearest->Coord().Distance(ni->Coord());
				auto val = std::min(theBase, ho + theGrowthRate * dx);
				if (val < ho) sources.at(id) = val;
			}
			{
				auto id = Index_Of(nearest->Index());

				auto h = sources.at(id);
				if (x->H() < h) sources.at(id) = x->H();
			}
		}
	}
}

std::vector<Standard_Real>
tnbLib::MeshBase_Tools::CalcDeterminants
(
	const std::vector<Pnt2d> & pts,
	const Entity2d_MetricMeshValue & theMs
)
{
	const auto& bMesh = theMs.Mesh();
	Debug_Null_Pointer(bMesh);

	auto elemnts = MakeMesh(*bMesh);
#ifdef _DEBUG
	if (elemnts.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list of elements is empty!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	auto start = elemnts.front();
	const auto& ms = theMs.Values();

	std::vector<Standard_Real> hs;
	hs.reserve(pts.size());
	for (const auto& x : pts)
	{
		auto loc = ElementLocation(start, x);
		if (NOT loc)
		{
			auto b = Entity2d_Box::BoundingBoxOf(bMesh->Points());
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the domain!" << endl
				<< " - coord: " << x << endl
				<< " - domain: " << b << endl
				<< abort(FatalError);
		}
		auto[v0, v1, v2] = loc->Nodes();

		const auto& m0 = ms.at(Index_Of(v0->Index()));
		const auto& m1 = ms.at(Index_Of(v1->Index()));
		const auto& m2 = ms.at(Index_Of(v2->Index()));

		auto det0 = m0.Determinant();
		auto det1 = m1.Determinant();
		auto det2 = m2.Determinant();

		auto ws = loc->InterpWeights(x);

		Standard_Real sumA = ws[0] + ws[1] + ws[2];
		Standard_Real numer = ws[0] * det0 + ws[1] * det1 + ws[2] * det2;

		auto h = (1.0 / sumA)*numer;
		hs.push_back(h);
	}
	return std::move(hs);
}

std::shared_ptr<tnbLib::Entity2d_MeshValue> 
tnbLib::MeshBase_Tools::CalcDeterminants
(
	const std::shared_ptr<Entity2d_Triangulation> & theAprx,
	const Entity2d_MetricMeshValue & theMs
)
{
	Debug_Null_Pointer(theAprx);

	const auto& bMesh = theMs.Mesh();
	Debug_Null_Pointer(bMesh);

	auto elemnts = MakeMesh(*bMesh);
#ifdef _DEBUG
	if (elemnts.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list of elements is empty!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	auto start = elemnts.front();

	const auto& ms = theMs.Values();
	const auto& pts = theAprx->Points();
	std::vector<Standard_Real> hs;
	hs.reserve(pts.size());
	for (const auto& x : pts)
	{
		auto loc = ElementLocation(start, x);
		if (NOT loc)
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the domain!" << endl
				<< " - coord: " << x << endl
				<< abort(FatalError);
		}
		auto[v0, v1, v2] = loc->Nodes();

		const auto& m0 = ms.at(Index_Of(v0->Index()));
		const auto& m1 = ms.at(Index_Of(v1->Index()));
		const auto& m2 = ms.at(Index_Of(v2->Index()));

		auto det0 = m0.Determinant();
		auto det1 = m1.Determinant();
		auto det2 = m2.Determinant();

		auto ws = loc->InterpWeights(x);
		
		Standard_Real sumA = ws[0] + ws[1] + ws[2];
		Standard_Real numer = ws[0] * det0 + ws[1] * det1 + ws[2] * det2;
		
		auto h = (1.0 / sumA)*numer;
		hs.push_back(h);
	}
	auto approximated = std::make_shared<Entity2d_MeshValue>();
	Debug_Null_Pointer(approximated);

	approximated->SetMesh(theAprx);
	approximated->SetValues(std::move(hs));
	return std::move(approximated);
}

tnbLib::Pnt2d 
tnbLib::MeshBase_Tools::CorrectCoord
(
	const Pnt2d & theCentre, 
	const Pnt2d & theCoord,
	const Entity2d_Box & theDomain
)
{
	const auto& p0 = theDomain.P0();
	const auto& p1 = theDomain.P1();

	const auto xmin = p0.X();
	const auto xmax = p1.X();
	const auto ymin = p0.Y();
	const auto ymax = p1.Y();

	const auto x0 = theCentre.X();
	const auto y0 = theCentre.Y();

	const auto xp = theCoord.X();
	const auto yp = theCoord.Y();

	if (xp > xmax)
	{
		const auto tx = (xmax - x0) / (xp - x0);
		if (yp > ymax)
		{
			const auto ty = (ymax - y0) / (yp - y0);
			const auto t = std::min(tx, ty);

			Pnt2d newPoint(x0 + t * (xp - x0), y0 + t * (yp - y0));
			return std::move(newPoint);
		}
		
		if (yp < ymin)
		{
			const auto ty = (ymin - y0) / (yp - y0);
			const auto t = std::min(tx, ty);

			Pnt2d newPoint(x0 + t * (xp - x0), y0 + t * (yp - y0));
			return std::move(newPoint);
		}
		const auto y = y0 + (yp - y0)*tx;

		Pnt2d newPoint(xmax, y);
		return std::move(newPoint);
	}

	if (xp < xmin)
	{
		const auto tx = (xmin - x0) / (xp - x0);
		if (yp > ymax)
		{
			const auto ty = (ymax - y0) / (yp - y0);
			const auto t = std::min(tx, ty);

			Pnt2d newPoint(x0 + t * (xp - x0), y0 + t * (yp - y0));
			return std::move(newPoint);
		}

		if (yp < ymin)
		{
			const auto ty = (ymin - y0) / (yp - y0);
			const auto t = std::min(tx, ty);

			Pnt2d newPoint(x0 + t * (xp - x0), y0 + t * (yp - y0));
			return std::move(newPoint);
		}
		const auto y = y0 + (yp - y0)*tx;

		Pnt2d newPoint(xmin, y);
		return std::move(newPoint);
	}
	
	if (yp > ymax)
	{
		const auto t = (ymax - y0) / (yp - y0);
		const auto x = x0 + (xp - x0)*t;

		Pnt2d newPoint(x, ymax);
		return std::move(newPoint);
	}

	if (yp < ymin)
	{
		const auto t = (ymin - y0) / (yp - y0);
		const auto x = x0 + (xp - x0)*t;

		Pnt2d newPoint(x, ymin);
		return std::move(newPoint);
	}

	Info << " - Coord: " << theCoord << endl;
	Info << " - Domain: " << theDomain << endl;
	FatalErrorIn(FunctionSIG)
		<< "unpredictable condition is occurred!" << endl
		<< abort(FatalError);
	return Pnt2d::null;
}

std::shared_ptr<tnbLib::Mesh3d_Edge> 
tnbLib::MeshBase_Tools::FindEdge
(
	const Mesh3d_Node& theNode0,
	const Mesh3d_Node& theNode1
)
{
	if (theNode1.NbEdges() < theNode0.NbEdges())
	{
		return FindEdge(theNode1, theNode0);
	}
	else
	{
		const auto& edges = theNode1.RetrieveEdges();
		for (const auto& x : edges)
		{
			auto id = x.first;
			if (theNode0.IsOnEdges(id))
			{
				return x.second.lock();
			}
		}
	}
	return nullptr;
}

const Handle(Geom2d_Curve)& 
tnbLib::MeshBase_Tools::Geometry
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->Geometry();
}

const Handle(Geom2d_Curve)&
tnbLib::MeshBase_Tools::Geometry
(
	const std::shared_ptr<TModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->Geometry();
}

const Handle(Geom2d_Curve)&
tnbLib::MeshBase_Tools::Geometry
(
	const std::shared_ptr<GModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->Geometry();
}

Standard_Real 
tnbLib::MeshBase_Tools::FirstParameter
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->FirstParameter();
}

Standard_Real
tnbLib::MeshBase_Tools::FirstParameter
(
	const std::shared_ptr<TModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->FirstParameter();
}

Standard_Real
tnbLib::MeshBase_Tools::FirstParameter
(
	const std::shared_ptr<GModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->FirstParameter();
}

Standard_Real
tnbLib::MeshBase_Tools::LastParameter
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->LastParameter();
}

Standard_Real
tnbLib::MeshBase_Tools::LastParameter
(
	const std::shared_ptr<TModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->LastParameter();
}

Standard_Real
tnbLib::MeshBase_Tools::LastParameter
(
	const std::shared_ptr<GModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->LastParameter();
}

std::vector<std::shared_ptr<tnbLib::Mesh2d_Node>>
tnbLib::MeshBase_Tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements
)
{
	auto cmp = [](const std::shared_ptr<Mesh2d_Node>& n0, const std::shared_ptr<Mesh2d_Node>& n1) 
	{return n0->Index() < n1->Index(); };
	std::set<std::shared_ptr<Mesh2d_Node>, decltype(cmp)> nodeSet(cmp);
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		auto [n0, n1, n2] = x->Nodes();
		nodeSet.insert(std::move(n0));
		nodeSet.insert(std::move(n1));
		nodeSet.insert(std::move(n2));
	}

	std::vector<std::shared_ptr<Mesh2d_Node>> nodes;
	std::copy(nodeSet.begin(), nodeSet.end(), std::back_inserter(nodes));
	/*nodes.reserve(nodeSet.size());
	for (auto& n : nodeSet)
	{
		nodes.push_back(std::move(n));
	}*/
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::Mesh3d_Node>> 
tnbLib::MeshBase_Tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements
)
{
	auto cmp = [](const std::shared_ptr<Mesh3d_Node>& n0, const std::shared_ptr<Mesh3d_Node>& n1) {return n0->Index() < n1->Index(); };
	std::set<std::shared_ptr<Mesh3d_Node>, decltype(cmp)> nodeSet(cmp);
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		auto[n0, n1, n2, n3] = x->Nodes();
		nodeSet.insert(std::move(n0));
		nodeSet.insert(std::move(n1));
		nodeSet.insert(std::move(n2));
		nodeSet.insert(std::move(n3));
	}

	std::vector<std::shared_ptr<Mesh3d_Node>> nodes;
	std::copy(nodeSet.begin(), nodeSet.end(), std::back_inserter(nodes));
	/*nodes.reserve(nodeSet.size());
	for (auto& n : nodeSet)
	{
		nodes.push_back(std::move(n));
	}*/
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::Mesh2d_Node>>
tnbLib::MeshBase_Tools::RetrieveAdjacentNodes
(
	const std::shared_ptr<Mesh2d_Node>& theNode
)
{
	Debug_Null_Pointer(theNode);
	const auto& edges = theNode->RetrieveEdges();
	std::vector<std::shared_ptr<Mesh2d_Node>> nodes;
	nodes.reserve(edges.size());
	for (const auto& x : edges)
	{
		auto e = x.second.lock();
		Debug_Null_Pointer(e);
		if (e->Node0() NOT_EQUAL theNode)
		{
			nodes.push_back(e->Node0());
			continue;
		}
		if (e->Node1() NOT_EQUAL theNode)
		{
			nodes.push_back(e->Node1());
		}
	}
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::Mesh3d_Node>>
tnbLib::MeshBase_Tools::RetrieveAdjacentNodes
(
	const std::shared_ptr<Mesh3d_Node>& theNode
)
{
	Debug_Null_Pointer(theNode);
	const auto& edges = theNode->RetrieveEdges();
	std::vector<std::shared_ptr<Mesh3d_Node>> nodes;
	nodes.reserve(edges.size());
	for (const auto& x : edges)
	{
		auto e = x.second.lock();
		Debug_Null_Pointer(e);
		if (e->Node0() NOT_EQUAL theNode)
		{
			nodes.push_back(e->Node0());
			continue;
		}
		if (e->Node1() NOT_EQUAL theNode)
		{
			nodes.push_back(e->Node1());
		}
	}
	return std::move(nodes);
}