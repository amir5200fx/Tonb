#include <Pln_Ring.hxx>

#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <Entity2d_Polygon.hxx>

Standard_Boolean 
tnbLib::Pln_Ring::IsDangle() const
{
	if (NOT Vtx())
	{
		FatalErrorIn(FunctionSIG)
			<< "the ring doesn't have a vertex" << endl
			<< abort(FatalError);
	}
	return Vtx()->IsDangle();
}

tnbLib::Pln_Ring::edgePoint 
tnbLib::Pln_Ring::GetPoint
(
	const std::shared_ptr<Pln_Vertex>& theVertex
) const
{
	if (theVertex NOT_EQUAL Vtx())
	{
		FatalErrorIn(FunctionSIG)
			<< "the vertex doesn't belong to the ring!" << endl
			<< abort(FatalError);
	}
	return edgePoint::first;
}

std::shared_ptr<tnbLib::Pln_Vertex> 
tnbLib::Pln_Ring::Vertex(const edgePoint thePoint) const
{
	return Vtx();
}

Standard_Boolean 
tnbLib::Pln_Ring::IsOrphan() const
{
	if (NOT Vtx())
	{
		FatalErrorIn(FunctionSIG)
			<< "the ring doesn't have a vertex" << endl
			<< abort(FatalError);
	}
	if (Vtx()->NbEdges() > 1)
	{
		return Standard_False;
	}
	if (Wire().lock())
	{
		return Standard_False;
	}
	return Standard_True;
}

Standard_Integer 
tnbLib::Pln_Ring::NbEntities
(
	const Pln_EntityType t
) const
{
	if (t IS_EQUAL Pln_EntityType::VERTEX)
		return 1;
	if (t IS_EQUAL Pln_EntityType::EDGE)
		return 1;
	return 0;
}

std::shared_ptr<tnbLib::Pln_Entity> 
tnbLib::Pln_Ring::Copy() const
{
	auto v = std::dynamic_pointer_cast<Pln_Vertex>(Vtx()->Copy());
	auto c = std::dynamic_pointer_cast<Pln_Curve>(Curve()->Copy());
	auto copy = std::make_shared<Pln_Ring>(Index(), Name(), std::move(v), std::move(c), Sense());
	Debug_Null_Pointer(copy);

	if (Vtx()->NbEdges())
	{
		v->InsertToEdges(copy->Index(), copy);
	}
	return std::move(copy);
}

void tnbLib::Pln_Ring::RetrieveEntitiesTo
(
	std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
	const Pln_EntityType t
) const
{
	if (t IS_EQUAL Pln_EntityType::VERTEX)
	{
		theEntities.push_back(Vtx());
	}
	if (t IS_EQUAL Pln_EntityType::EDGE)
	{
		theEntities.push_back(std::dynamic_pointer_cast<Pln_Entity>(This()));
	}
}

void tnbLib::Pln_Ring::Transform(const gp_Trsf2d & t)
{
	if (NOT IsOrphan())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge must be orphan for transforming" << endl
			<< abort(FatalError);
	}

	Curve()->Transform(t);
	Vtx()->Transform(t);

	if (Mesh())
		Mesh()->Transform(t);
}

void tnbLib::Pln_Ring::Reverse(const Standard_Boolean ApplyToMesh)
{
	if (ApplyToMesh)
	{
		/*if (Mesh())
		{
			Mesh()->Reverse();
		}*/
	}
	ChangeSense() = NOT Sense();
}