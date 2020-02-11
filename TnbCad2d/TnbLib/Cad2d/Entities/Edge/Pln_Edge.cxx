#include <Pln_Edge.hxx>

#include <Entity2d_Polygon.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>

#include <Geom2d_Curve.hxx>

Standard_Boolean 
tnbLib::Pln_Edge::IsDangle() const
{
	return Vtx0()->IsDangle() OR Vtx1()->IsDangle();
}

Standard_Integer 
tnbLib::Pln_Edge::GetIndex
(
	const std::shared_ptr<Pln_Vertex>& theVertex
) const
{
	if (Vtx0() IS_EQUAL theVertex)
	{
		return 0;
	}
	else if (Vtx1() IS_EQUAL theVertex)
	{
		return 1;
	}

	FatalErrorIn("Standard_Integer Index(const std::shared_ptr<Pln_Vertex>& theVertex) const")
		<< "the vertex is not on the edge" << endl
		<< abort(FatalError);
	return 0;
}

Standard_Real 
tnbLib::Pln_Edge::Parameter
(
	const Standard_Integer theIndex
) const
{
	if (Sense())
	{
		if (theIndex IS_EQUAL 0)
		{
			return Curve()->Geometry()->FirstParameter();
		}
		else if (theIndex IS_EQUAL 1)
		{
			return Curve()->Geometry()->LastParameter();
		}
		else
		{
			FatalErrorIn("Standard_Real Parameter(const Standard_Integer theIndex) const")
				<< "Invalid Index: " << theIndex << ", must be 0 or 1" << endl
				<< abort(FatalError);
			return 0;
		}
	}
	else
	{
		if (theIndex IS_EQUAL 0)
		{
			return Curve()->Geometry()->LastParameter();
		}
		else if (theIndex IS_EQUAL 1)
		{
			return Curve()->Geometry()->FirstParameter();
		}
		else
		{
			FatalErrorIn("Standard_Real Parameter(const Standard_Integer theIndex) const")
				<< "Invalid Index: " << theIndex << ", must be 0 or 1" << endl
				<< abort(FatalError);
			return 0;
		}
	}
}

void tnbLib::Pln_Edge::Reverse
(
	const Standard_Boolean ApplyToMesh
)
{
	std::swap(theVtx0_, theVtx1_);
	if (ApplyToMesh)
	{
		if (Mesh())
		{
			Mesh()->Reverse();
		}
	}

	ChangeSense() = NOT Sense();
}

Standard_Boolean 
tnbLib::Pln_Edge::IsConnected
(
	const std::shared_ptr<Pln_Edge>& theEdge0,
	const std::shared_ptr<Pln_Edge>& theEdge1,
	std::shared_ptr<Pln_Vertex>& theVtx
)
{
	const auto& v0 = theEdge0->Vtx0();
	const auto& v1 = theEdge0->Vtx1();

	const auto& q0 = theEdge1->Vtx0();
	const auto& q1 = theEdge1->Vtx1();

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