#include <Pln_Edge.hxx>

#include <Entity2d_Box.hxx>
#include <Entity2d_Polygon.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Ring.hxx>

#include <Geom2d_Curve.hxx>

const std::string tnbLib::Pln_Edge::extension = ".edge2d";

//Standard_Boolean 
//tnbLib::Pln_Edge::IsDangle() const
//{
//	return Vtx0()->IsDangle() OR Vtx1()->IsDangle();
//}

//Standard_Boolean
//tnbLib::Pln_Edge::IsOrphan() const
//{
//	if (Vtx0()->NbEdges() NOT_EQUAL 1)
//		return Standard_False;
//	if (Vtx1()->NbEdges() NOT_EQUAL 1)
//		return Standard_False;
//
//	if (Wire().lock())
//		return Standard_False;
//
//	return Standard_True;
//}

Standard_Integer 
tnbLib::Pln_Edge::NbEntities
(
	const Pln_EntityType t
) const
{
	if (t IS_EQUAL Pln_EntityType::VERTEX)
		return 2;
	if (t IS_EQUAL Pln_EntityType::EDGE)
		return 1;
	return 0;
}

//Standard_Integer 
//tnbLib::Pln_Edge::GetIndex
//(
//	const std::shared_ptr<Pln_Vertex>& theVertex
//) const
//{
//	if (Vtx0() IS_EQUAL theVertex)
//	{
//		return 0;
//	}
//	else if (Vtx1() IS_EQUAL theVertex)
//	{
//		return 1;
//	}
//
//	FatalErrorIn("Standard_Integer Index(const std::shared_ptr<Pln_Vertex>& theVertex) const")
//		<< "the vertex is not on the edge" << endl
//		<< abort(FatalError);
//	return 0;
//}

Standard_Real 
tnbLib::Pln_Edge::Parameter
(
	const edgePoint theIndex
) const
{
	if (Sense())
	{
		if (theIndex IS_EQUAL edgePoint::first)
		{
			return Curve()->Geometry()->FirstParameter();
		}
		else if (theIndex IS_EQUAL edgePoint::last)
		{
			return Curve()->Geometry()->LastParameter();
		}
		else
		{
			FatalErrorIn("Standard_Real Parameter(const Standard_Integer theIndex) const")
				<< "Unspecified type of point has been detected" << endl
				<< abort(FatalError);
			return 0;
		}
	}
	else
	{
		if (theIndex IS_EQUAL edgePoint::first)
		{
			return Curve()->Geometry()->LastParameter();
		}
		else if (theIndex IS_EQUAL edgePoint::last)
		{
			return Curve()->Geometry()->FirstParameter();
		}
		else
		{
			FatalErrorIn("Standard_Real Parameter(const Standard_Integer theIndex) const")
				<< "Unspecified type of point has been detected" << endl
				<< abort(FatalError);
			return 0;
		}
	}
}

tnbLib::Entity2d_Box 
tnbLib::Pln_Edge::BoundingBox
(
	const Standard_Real Tol
) const
{
	Debug_Null_Pointer(Curve());
	auto b = Curve()->BoundingBox(Tol);
	return std::move(b);
}

//std::shared_ptr<tnbLib::Pln_Entity> 
//tnbLib::Pln_Edge::Copy() const
//{
//	auto v0 = std::dynamic_pointer_cast<Pln_Vertex>(Vtx0()->Copy());
//	auto v1 = std::dynamic_pointer_cast<Pln_Vertex>(Vtx1()->Copy());
//	auto c = std::dynamic_pointer_cast<Pln_Curve>(Curve()->Copy());
//
//	if (v0 IS_EQUAL v1)
//	{
//		auto copy = std::make_shared<Pln_Ring>(Index(), Name(), v0, c, Sense());
//		Debug_Null_Pointer(copy);
//
//		v0->InsertToEdges(copy->Index(), copy);
//
//		return std::move(copy);
//	}
//	else
//	{
//		Debug_Null_Pointer(v0);
//		Debug_Null_Pointer(v1);
//
//		auto copy = std::make_shared<Pln_Edge>(Index(), Name(), v0, v1, c, Sense());
//		Debug_Null_Pointer(copy);
//
//		v0->InsertToEdges(copy->Index(), copy);
//		v1->InsertToEdges(copy->Index(), copy);
//
//		return std::move(copy);
//	}
//}

tnbLib::Pln_EntityType 
tnbLib::Pln_Edge::Type() const
{
	return Pln_EntityType::EDGE;
}

std::shared_ptr<tnbLib::Pln_Vertex> 
tnbLib::Pln_Edge::FirstVtx() const
{
	return Vertex(edgePoint::first);
}

std::shared_ptr<tnbLib::Pln_Vertex> 
tnbLib::Pln_Edge::LastVtx() const
{
	return Vertex(edgePoint::last);
}

//void tnbLib::Pln_Edge::Transform
//(
//	const gp_Trsf2d & t
//)
//{
//	if (NOT IsOrphan())
//	{
//		FatalErrorIn("void tnbLib::Pln_Edge::Transform(const gp_Trsf2d & t)")
//			<< "the edge must be orphan for transforming" << endl
//			<< abort(FatalError);
//	}
//
//	Curve()->Transform(t);
//	Vtx0()->Transform(t);
//	if (NOT IsRing())
//	{
//		Vtx1()->Transform(t);
//	}
//
//	if(Mesh())
//		Mesh()->Transform(t);
//}

//void tnbLib::Pln_Edge::RetrieveEntitiesTo
//(
//	std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
//	const Pln_EntityType t
//) const
//{
//	if (t IS_EQUAL Pln_EntityType::VERTEX)
//	{
//		theEntities.push_back(Vtx0());
//		theEntities.push_back(Vtx1());
//	}
//	if (t IS_EQUAL Pln_EntityType::EDGE)
//	{
//		theEntities.push_back(std::dynamic_pointer_cast<Pln_Entity>(This()));
//	}
//}

//void tnbLib::Pln_Edge::Reverse
//(
//	const Standard_Boolean ApplyToMesh
//)
//{
//	std::swap(theVtx0_, theVtx1_);
//	if (ApplyToMesh)
//	{
//		/*if (Mesh())
//		{
//			Mesh()->Reverse();
//		}*/
//	}
//
//	ChangeSense() = NOT Sense();
//}

Standard_Boolean 
tnbLib::Pln_Edge::IsConnected
(
	const std::shared_ptr<Pln_Edge>& theEdge0,
	const std::shared_ptr<Pln_Edge>& theEdge1,
	std::shared_ptr<Pln_Vertex>& theVtx
)
{
	const auto v0 = theEdge0->FirstVtx();
	const auto v1 = theEdge0->LastVtx();

	const auto q0 = theEdge1->FirstVtx();
	const auto q1 = theEdge1->LastVtx();

	if (v0 IS_EQUAL q0)
	{
		theVtx = v0;
		return Standard_True;
	}
	else if (v0 IS_EQUAL q1)
	{
		theVtx = v0;
		return Standard_True;
	}
	else if (v1 IS_EQUAL q0)
	{
		theVtx = v1;
		return Standard_True;
	}
	else if (v1 IS_EQUAL q1)
	{
		theVtx = v1;
		return Standard_True;
	}

	theVtx = nullptr;
	return Standard_False;
}