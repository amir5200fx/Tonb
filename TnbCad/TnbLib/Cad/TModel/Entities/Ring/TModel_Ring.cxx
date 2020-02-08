#include <TModel_Ring.hxx>

tnbLib::TModel_Ring::TModel_Ring
(
	const std::shared_ptr<TModel_Vertex>& theVtx, 
	const std::shared_ptr<TModel_Curve>& theCurve,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve, 
	const Standard_Boolean theSense
)
	: TModel_Edge(theVtx, theVtx, theCurve, theParaCurve, theSense)
{
}

tnbLib::TModel_Ring::TModel_Ring
(
	const Standard_Integer theIndex,
	const std::shared_ptr<TModel_Vertex>& theVtx,
	const std::shared_ptr<TModel_Curve>& theCurve,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: TModel_Edge(theIndex, theVtx, theVtx, theCurve, theParaCurve, theSense)
{
}

tnbLib::TModel_Ring::TModel_Ring
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<TModel_Vertex>& theVtx,
	const std::shared_ptr<TModel_Curve>& theCurve,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: TModel_Edge(theIndex, theName, theVtx, theVtx, theCurve, theParaCurve, theSense)
{
}

tnbLib::TModel_Ring::TModel_Ring
(
	const std::shared_ptr<TModel_Curve>& theCurve,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve, 
	const Standard_Boolean theSense
)
	: TModel_Edge(theCurve, theParaCurve, theSense)
{
}

tnbLib::TModel_Ring::TModel_Ring
(
	const Standard_Integer theIndex,
	const std::shared_ptr<TModel_Curve>& theCurve,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: TModel_Edge(theIndex, theCurve, theParaCurve, theSense)
{
}

tnbLib::TModel_Ring::TModel_Ring
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<TModel_Curve>& theCurve,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: TModel_Edge(theIndex, theName, theCurve, theParaCurve, theSense)
{
}