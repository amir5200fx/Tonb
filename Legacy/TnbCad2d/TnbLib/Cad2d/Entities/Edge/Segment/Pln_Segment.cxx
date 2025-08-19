#include <Pln_Segment.hxx>

#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::Pln_Segment::IsDangle() const
{
	if (NOT Vtx0())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge has no v0 vertex" << endl
			<< abort(FatalError);
	}
	if (NOT Vtx1())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge has no v1 vertex" << endl
			<< abort(FatalError);
	}
	return Vtx0()->IsDangle() OR Vtx1()->IsDangle();
}

Standard_Boolean 
tnbLib::Pln_Segment::IsOrphan() const
{
	if (NOT Vtx0())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge has no v0 vertex" << endl
			<< abort(FatalError);
	}
	if (NOT Vtx1())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge has no v1 vertex" << endl
			<< abort(FatalError);
	}
	if (Vtx0()->NbEdges() NOT_EQUAL 1)
		return Standard_False;
	if (Vtx1()->NbEdges() NOT_EQUAL 1)
		return Standard_False;

	if (Wire().lock())
		return Standard_False;

	return Standard_True;
}

tnbLib::Pln_Edge::edgePoint 
tnbLib::Pln_Segment::GetPoint
(
	const std::shared_ptr<Pln_Vertex>& theVertex
) const
{
	if (Vtx0() IS_EQUAL theVertex)
	{
		return Pln_Edge::edgePoint::first;
	}
	else if (Vtx1() IS_EQUAL theVertex)
	{
		return Pln_Edge::edgePoint::last;
	}

	FatalErrorIn(FunctionSIG)
		<< "the vertex is not on the edge" << endl
		<< abort(FatalError);
	return Pln_Edge::edgePoint::first;
}

std::shared_ptr<tnbLib::Pln_Vertex> 
tnbLib::Pln_Segment::Vertex(const edgePoint thePoint) const
{
	if (thePoint IS_EQUAL edgePoint::first)
	{
		return Vtx0();
	}
	else if (thePoint IS_EQUAL edgePoint::last)
	{
		return Vtx1();
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "unspecified type of point has been detected!" << endl
			<< abort(FatalError);
	}
	return std::make_shared<tnbLib::Pln_Vertex>();
}

std::shared_ptr<tnbLib::Pln_Entity> 
tnbLib::Pln_Segment::Copy() const
{
	auto v0 = std::dynamic_pointer_cast<Pln_Vertex>(Vtx0()->Copy());
	auto v1 = std::dynamic_pointer_cast<Pln_Vertex>(Vtx1()->Copy());
	auto c = std::dynamic_pointer_cast<Pln_Curve>(Curve()->Copy());

	Debug_Null_Pointer(v0);
	Debug_Null_Pointer(v1);

	auto copy = std::make_shared<Pln_Segment>(Index(), Name(), std::move(v0), std::move(v1), std::move(c), Sense());
	Debug_Null_Pointer(copy);

	v0->InsertToEdges(copy->Index(), copy);
	v1->InsertToEdges(copy->Index(), copy);

	return std::move(copy);
}

void tnbLib::Pln_Segment::RetrieveEntitiesTo
(
	std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
	const Pln_EntityType t
) const
{
	if (t IS_EQUAL Pln_EntityType::VERTEX)
	{
		theEntities.push_back(Vtx0());
		theEntities.push_back(Vtx1());
	}
	if (t IS_EQUAL Pln_EntityType::EDGE)
	{
		theEntities.push_back(std::dynamic_pointer_cast<Pln_Entity>(This()));
	}
}

void tnbLib::Pln_Segment::Transform(const gp_Trsf2d & t)
{
	if (NOT IsOrphan())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge must be orphan for transforming" << endl
			<< abort(FatalError);
	}

	Curve()->Transform(t);
	Vtx0()->Transform(t);
	Vtx1()->Transform(t);

	if (Mesh())
		Mesh()->Transform(t);
}

void tnbLib::Pln_Segment::Reverse
(
	const Standard_Boolean ApplyToMesh
)
{
	std::swap(theVtx0_, theVtx1_);
	if (ApplyToMesh)
	{
		/*if (Mesh())
		{
			Mesh()->Reverse();
		}*/
	}

	ChangeSense() = NOT Sense();
}