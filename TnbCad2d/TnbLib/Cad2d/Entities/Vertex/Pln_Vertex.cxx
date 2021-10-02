#include <Pln_Vertex.hxx>

#include <Entity2d_Box.hxx>
#include <Entity2d_Polygon.hxx>
#include <Pln_Ring.hxx>

Standard_Boolean 
tnbLib::Pln_Vertex::IsRingPoint() const
{
	if (NbEdges() NOT_EQUAL 1) return Standard_False;

	std::vector<std::weak_ptr<Pln_Edge>> edges;
	RetrieveEdgesTo(edges);

	if (std::dynamic_pointer_cast<Pln_Ring>(edges[0].lock()))
	{
		return Standard_True;
	}
	return Standard_False;
}

Standard_Boolean 
tnbLib::Pln_Vertex::IsManifold() const
{
	if (IsRingPoint()) return Standard_True;
	else if (NbEdges() IS_EQUAL 2) return Standard_True;
	return Standard_False;
}

Standard_Real 
tnbLib::Pln_Vertex::CalcGap() const
{
	if (NOT IsManifold())
	{
		FatalErrorIn(FunctionSIG)
			<< "the corner is not manifold!" << endl
			<< abort(FatalError);
		return 0;
	}

	if (IsRingPoint())
	{
		const auto edge = Edges().begin()->second.lock();
		Debug_Null_Pointer(edge);

		const auto& mesh = edge->Mesh();
		if (NOT mesh)
		{
			FatalErrorIn(FunctionSIG)
				<< "the edge has no mesh" << endl
				<< abort(FatalError);
		}
		const auto& pnts = mesh->Points();
		return FirstItem(pnts).Distance(LastItem(pnts));
	}
	else
	{
		auto edge0 = BackWardEdge();
		Debug_Null_Pointer(edge0);

		auto edge1 = ForwardEdge();
		Debug_Null_Pointer(edge1);

		auto p0 = edge0->LastCoord(edge0->Sense());
		auto p1 = edge1->FirstCoord(edge1->Sense());

		return p0.Distance(p1);
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::Pln_Vertex::BackWardEdge() const
{
	if (NOT IsManifold())
	{
		FatalErrorIn(FunctionSIG)
			<< "the corner is not manifold!" << endl
			<< abort(FatalError);
		return nullptr;
	}
	auto edges = RetrieveEdges();
	if (edges.size() IS_EQUAL 1)
	{
		auto e = edges[0].lock();
		return std::move(e);
	}
	else if (edges.size() IS_EQUAL 2)
	{
		auto thisPtr = std::dynamic_pointer_cast<Pln_Vertex>(This());

		auto e0 = edges[0].lock();
		Debug_Null_Pointer(e0);

		if (e0->Vtx1() IS_EQUAL thisPtr)
		{
			return std::move(e0);
		}

		auto e1 = edges[1].lock();
		Debug_Null_Pointer(e1);

		if (e1->Vtx1() IS_EQUAL thisPtr)
		{
			return std::move(e1);
		}

		FatalErrorIn(FunctionSIG)
			<< "no backward edge has been found!" << endl
			<< abort(FatalError);
		return nullptr;
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data have been detected!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::Pln_Vertex::ForwardEdge() const
{
	if (NOT IsManifold())
	{
		FatalErrorIn(FunctionSIG)
			<< "the corner is not manifold!" << endl
			<< abort(FatalError);
		return nullptr;
	}
	auto edges = RetrieveEdges();
	if (edges.size() IS_EQUAL 1)
	{
		auto e = edges[0].lock();
		return std::move(e);
	}
	else if (edges.size() IS_EQUAL 2)
	{
		auto thisPtr = std::dynamic_pointer_cast<Pln_Vertex>(This());

		auto e0 = edges[0].lock();
		Debug_Null_Pointer(e0);

		if (e0->Vtx0() IS_EQUAL thisPtr)
		{
			return std::move(e0);
		}

		auto e1 = edges[1].lock();
		Debug_Null_Pointer(e1);

		if (e1->Vtx0() IS_EQUAL thisPtr)
		{
			return std::move(e1);
		}

		FatalErrorIn(FunctionSIG)
			<< "no backward edge has been found!" << endl
			<< abort(FatalError);
		return nullptr;
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data have been detected!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

tnbLib::Entity2d_Box 
tnbLib::Pln_Vertex::BoundingBox
(
	const Standard_Real Tol
) const
{
	Entity2d_Box b(Coord() - Tol, Coord() + Tol);
	return std::move(b);
}

std::shared_ptr<tnbLib::Pln_Entity> 
tnbLib::Pln_Vertex::Copy() const
{
	auto copy = std::make_shared<Pln_Vertex>(Index(), Name(), Coord());
	return std::move(copy);
}

tnbLib::Pln_EntityType 
tnbLib::Pln_Vertex::Type() const
{
	return Pln_EntityType::VERTEX;
}

void tnbLib::Pln_Vertex::Transform
(
	const gp_Trsf2d & t
)
{
	if (NOT IsOrphan())
	{
		FatalErrorIn("void Transform(const gp_Trsf2d& t)")
			<< "the vertex must be orphan for transforming" << endl
			<< abort(FatalError);
	}
	Coord().Transform(t);
}

void tnbLib::Pln_Vertex::RetrieveEntitiesTo
(
	std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
	const Pln_EntityType t
) const
{
	if (t IS_EQUAL Pln_EntityType::VERTEX)
	{
		theEntities.push_back(std::dynamic_pointer_cast<Pln_Entity>(This()));
	}
}