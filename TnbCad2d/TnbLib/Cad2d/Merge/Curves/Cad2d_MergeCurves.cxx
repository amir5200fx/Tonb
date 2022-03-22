#include <Cad2d_MergeCurves.hxx>

#include <Cad2d_MergeCurvesInfo.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Vertex.hxx>
#include <Geo_PrTree.hxx>
#include <Entity2d_Box.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Cad2d_MergeCurves::Node::InsertTo
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pln_Vertex>& theVtx
)
{
	Global_Tools::Insert(theIndex, theVtx, theVertices_);
}

const tnbLib::Pnt2d& 
tnbLib::Cad2d_MergeCurves::Node::GetCoord
(
	const std::shared_ptr<Node>& theNode
)
{
	Debug_Null_Pointer(theNode);
	return theNode->Coord();
}

std::map<Standard_Integer, std::shared_ptr<tnbLib::Cad2d_MergeCurves::Node>>
tnbLib::Cad2d_MergeCurves::RetrieveNodes
(
	const std::vector<std::shared_ptr<Link>>& theLinks
)
{
	std::map<Standard_Integer, std::shared_ptr<Node>> nodes;
	for (const auto& x : theLinks)
	{
		Debug_Null_Pointer(x);
		if (auto ring = std::dynamic_pointer_cast<RingLink>(x))
		{
			Global_Tools::InsertIgnoreDup(ring->GetNode()->Index(), ring->GetNode(), nodes);
		}
		else if (auto seg = std::dynamic_pointer_cast<SegmentLink>(x))
		{
			Global_Tools::InsertIgnoreDup(seg->Node0()->Index(), seg->Node0(), nodes);
			Global_Tools::InsertIgnoreDup(seg->Node1()->Index(), seg->Node1(), nodes);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of link has been detected!" << endl
				<< abort(FatalError);
		}
	}
	return std::move(nodes);
}

namespace tnbLib
{
	auto CalcMeanCoord(const std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>>& vertices)
	{
		Pnt2d c(0, 0);
		for (const auto& x : vertices)
		{
			Debug_Null_Pointer(x.second);
			const auto& vtx = x.second;
			c += vtx->Coord();
		}
		c /= (Standard_Real)vertices.size();
		
		Standard_Real tol = 0;
		for (const auto& x : vertices)
		{
			const auto& vtx = x.second;
			auto dis = Distance(c, vtx->Coord());
			if (dis > tol)
			{
				tol = dis;
			}
		}
		auto t = std::make_pair(std::move(c), tol);
		return std::move(t);
	}
}

std::shared_ptr<tnbLib::Pln_Vertex>
tnbLib::Cad2d_MergeCurves::MergeNode
(
	const std::shared_ptr<Node>& theNode
)
{
	Debug_Null_Pointer(theNode);
	const auto& vertices = theNode->Vertices();
	const auto [m, tol] = CalcMeanCoord(vertices);
	auto v = std::make_shared<Pln_Vertex>(theNode->Index(), std::move(m));
	v->SetPrecision(tol);
	return std::move(v);
}

std::vector<std::shared_ptr<tnbLib::Cad2d_MergeCurves::Link>> 
tnbLib::Cad2d_MergeCurves::CreateLinks
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theCurves
) const
{
	static auto insert_to_engine = [](
		Geo_PrTree<std::shared_ptr<Node>>& engine,
		const std::shared_ptr<Pln_Vertex>& vtx,
		const Standard_Real radius, const Standard_Real tol
		)
	{
		const auto dr = Pnt2d(radius, radius);
		const auto& coord = vtx->Coord();
		std::vector<std::shared_ptr<Node>> candidates;
		
		const auto p0 = coord - dr;
		const auto p1 = coord + dr;

		Entity2d_Box d(std::move(p0), std::move(p1));
		engine.GeometrySearch(d, candidates);
		if (candidates.empty())
		{
			auto n = std::make_shared<Node>(engine.Size() + 1);
			n->InsertTo(vtx->Index(), vtx);
			n->SetCoord(coord);
			n->SetTolerance(0);

			engine.InsertToGeometry(n);
			return std::move(n);
		}
		else
		{
			auto minDis = RealLast();
			std::shared_ptr<Node> found;

			for (const auto& x : candidates)
			{
				Debug_Null_Pointer(x);
				auto dis = Distance(x->Coord(), coord);
				if (dis < minDis)
				{
					minDis = dis;
					found = x;
				}
			}

			if (minDis <= tol)
			{
				found->InsertTo(vtx->Index(), vtx);
				found->SetTolerance(std::max(found->Tolerance(), minDis));
				return std::move(found);
			}
			else
			{
				auto n = std::make_shared<Node>(engine.Size() + 1);
				n->InsertTo(vtx->Index(), vtx);
				n->SetCoord(coord);
				n->SetTolerance(0);

				engine.InsertToGeometry(n);
				return std::move(n);
			}
		}
	};

	const auto domain = Entity2d_Box::BoundingBoxOf(RetrieveCoords(theCurves));
	const auto radius = AlgInfo()->Radius();
	const auto tol = AlgInfo()->Tolerance();

	Geo_PrTree<std::shared_ptr<Node>> engine;
	engine.SetGeometryCoordFunc(&Node::GetCoord);
	engine.SetGeometryRegion(domain.OffSet(1.0E-3 * domain.Diameter()));

	std::vector<std::shared_ptr<Link>> links;
	links.reserve(theCurves.size());

	Standard_Integer k = 0;
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);

		std::vector<std::shared_ptr<Node>> candidates;
		if (x->IsRing())
		{
			const auto& vtx = x->Vtx0();
			Debug_Null_Pointer(vtx);

			auto n = insert_to_engine(engine, vtx, radius, tol);
			Debug_Null_Pointer(n);

			auto ring = std::make_shared<RingLink>(++k, std::move(n));
			links.push_back(std::move(ring));
		}
		else
		{
			const auto& vtx0 = x->Vtx0();
			const auto& vtx1 = x->Vtx1();
			Debug_Null_Pointer(vtx0);
			Debug_Null_Pointer(vtx1);

			auto n0 = insert_to_engine(engine, vtx0, radius, tol);
			auto n1 = insert_to_engine(engine, vtx1, radius, tol);
			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			auto seg = std::make_shared<SegmentLink>(++k, std::move(n0), std::move(n1));
			links.push_back(std::move(seg));
		}
	}
	return std::move(links);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::Cad2d_MergeCurves::RetrieveCoords
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	std::vector<Pnt2d> coords;
	coords.reserve(2 * theEdges.size());
	for (const auto& x : theEdges)
	{
		if (x->IsRing())
		{
			const auto& v0 = x->Vtx0();
			coords.push_back(v0->Coord());
		}
		else
		{
			const auto& v0 = x->Vtx0();
			const auto& v1 = x->Vtx1();

			coords.push_back(v0->Coord());
			coords.push_back(v1->Coord());
		}
	}
	return std::move(coords);
}

void tnbLib::Cad2d_MergeCurves::Perform()
{
	if (Curves().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve list is empty!" << endl
			<< abort(FatalError);
	}
	auto links = CreateLinks(Curves());
	auto nodes = RetrieveNodes(links);

	std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>> vertices;
	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x.second);
		auto v = MergeNode(x.second);
		Global_Tools::Insert(v->Index(), std::move(v), vertices);
	}

	for (const auto& x : links)
	{
		const auto& ed = x->Curve();

		if (auto ring = std::dynamic_pointer_cast<RingLink>(x))
		{
			const auto& n = ring->GetNode();

			auto v = Global_Tools::Find(vertices, n->Index());

			v->InsertToEdges(ed->Index(), ed);

			ed->ChangeVtx0() = v;
			ed->ChangeVtx1() = v;
		}
		else if (auto seg = std::dynamic_pointer_cast<SegmentLink>(x))
		{
			const auto& n0 = seg->Node0();
			const auto& n1 = seg->Node1();

			auto v0 = Global_Tools::Find(vertices, n0->Index());
			auto v1 = Global_Tools::Find(vertices, n1->Index());

			v0->InsertToEdges(ed->Index(), ed);
			v1->InsertToEdges(ed->Index(), ed);

			ed->ChangeVtx0() = v0;
			ed->ChangeVtx1() = v1;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of link has been detected!" << endl
				<< abort(FatalError);
		}
	}
	Change_IsDone() = Standard_True;
}

namespace tnbLib
{
	auto RetrieveVertices(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges)
	{
		std::vector<std::shared_ptr<Pln_Vertex>> vertices;
		vertices.reserve(2 * theEdges.size());
		for (const auto& x : theEdges)
		{
			Debug_Null_Pointer(x);
			if (x->IsRing())
			{
				vertices.push_back(x->Vtx0());
			}
			else
			{
				vertices.push_back(x->Vtx0());
				vertices.push_back(x->Vtx1());
			}
		}
		return std::move(vertices);
	}
}

const std::shared_ptr<tnbLib::Cad2d_MergeCurvesInfo> tnbLib::Cad2d_MergeCurves::DEFAULT_INFO =
std::make_shared<tnbLib::Cad2d_MergeCurvesInfo>();

void tnbLib::Cad2d_MergeCurves::Renumber
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	{// renumber the vertices [3/22/2022 Amir]
		auto vertices = RetrieveVertices(theEdges);
		Standard_Integer k = 0;
		for (const auto& x : vertices)
		{
			Debug_Null_Pointer(x);
			x->SetIndex(++k);
		}
	}
	Standard_Integer k = 0;
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		x->SetIndex(++k);
	}
}