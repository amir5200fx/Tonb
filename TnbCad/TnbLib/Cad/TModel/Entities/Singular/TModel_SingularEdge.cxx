#include <TModel_SingularEdge.hxx>

tnbLib::TModel_SingularEdge::TModel_SingularEdge
(
	const std::shared_ptr<TModel_Vertex>& theVtx,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve
)
	: TModel_Edge(theVtx, theVtx, nullptr, theParaCurve, Standard_True)
{
}

tnbLib::TModel_SingularEdge::TModel_SingularEdge
(
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve
)
	: TModel_Edge(nullptr, theParaCurve)
{
}

tnbLib::TModel_SingularEdge::TModel_SingularEdge
(
	const Standard_Integer theIndex,
	const std::shared_ptr<TModel_Vertex>& theVtx,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve
)
	: TModel_Edge(theIndex, theVtx, theVtx, nullptr, theParaCurve)
{
}

tnbLib::TModel_SingularEdge::TModel_SingularEdge
(
	const Standard_Integer theIndex,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve
)
	: TModel_Edge(theIndex, nullptr, theParaCurve)
{
}

tnbLib::TModel_SingularEdge::TModel_SingularEdge
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<TModel_Vertex>& theVtx, 
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve
)
	: TModel_Edge(theIndex, theName, theVtx, theVtx, nullptr, theParaCurve)
{
}

tnbLib::TModel_SingularEdge::TModel_SingularEdge
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve
)
	: TModel_Edge(theIndex, theName, nullptr, theParaCurve)
{
}