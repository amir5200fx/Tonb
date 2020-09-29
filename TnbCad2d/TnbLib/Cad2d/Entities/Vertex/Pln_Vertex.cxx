#include <Pln_Vertex.hxx>

#include <Entity2d_Box.hxx>
#include <Pln_Ring.hxx>

Standard_Boolean tnbLib::Pln_Vertex::IsRingPoint() const
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

Standard_Boolean tnbLib::Pln_Vertex::IsManifold() const
{
	if (IsRingPoint()) return Standard_True;
	else if (NbEdges() IS_EQUAL 2) return Standard_True;
	return Standard_False;
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