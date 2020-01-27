#include <Pln_Edge.hxx>

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