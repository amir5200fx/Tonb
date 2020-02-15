#include <Pln_TangEdge.hxx>

tnbLib::Pln_TangEdge::Pln_TangEdge
(
	const std::shared_ptr<Pln_Vertex>& theVtx0, 
	const std::shared_ptr<Pln_Vertex>& theVtx1
)
	: Pln_Edge(theVtx0, theVtx1)
{
}

tnbLib::Pln_TangEdge::Pln_TangEdge
(
	const std::shared_ptr<Pln_Vertex>& theVtx0,
	const std::shared_ptr<Pln_Vertex>& theVtx1, 
	const std::shared_ptr<Pln_Curve>& theCurve, 
	const Standard_Boolean Sense
)
	: Pln_Edge(theVtx0, theVtx1, theCurve, Sense)
{
}

tnbLib::Pln_TangEdge::Pln_TangEdge
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Pln_Vertex>& theVtx0,
	const std::shared_ptr<Pln_Vertex>& theVtx1
)
	: Pln_Edge(theIndex, theVtx0, theVtx1)
{
}

tnbLib::Pln_TangEdge::Pln_TangEdge
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<Pln_Vertex>& theVtx0, 
	const std::shared_ptr<Pln_Vertex>& theVtx1
)
	: Pln_Edge(theIndex, theName, theVtx0, theVtx1)
{
}

tnbLib::Pln_TangEdge::Pln_TangEdge
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<Pln_Vertex>& theVtx0, 
	const std::shared_ptr<Pln_Vertex>& theVtx1, 
	const std::shared_ptr<Pln_Curve>& theCurve, 
	const Standard_Boolean Sense
)
	: Pln_Edge(theIndex, theName, theVtx0, theVtx1, theCurve, Sense)
{
}