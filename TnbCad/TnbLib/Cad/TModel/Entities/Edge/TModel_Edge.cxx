#include <TModel_Edge.hxx>

tnbLib::TModel_Edge::TModel_Edge
(
	const std::shared_ptr<TModel_Vertex>& theVtx0, 
	const std::shared_ptr<TModel_Vertex>& theVtx1, 
	const std::shared_ptr<TModel_Curve>& theCurve, 
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve, 
	const Standard_Boolean theSense
)
	: TModel_EdgeGeometry(theCurve, theParaCurve, theSense)
	, theVtx0_(theVtx0)
	, theVtx1_(theVtx1)
{
}

tnbLib::TModel_Edge::TModel_Edge
(
	const std::shared_ptr<TModel_Curve>& theCurve,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: TModel_EdgeGeometry(theCurve, theParaCurve, theSense)
{
}

tnbLib::TModel_Edge::TModel_Edge
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<TModel_Vertex>& theVtx0, 
	const std::shared_ptr<TModel_Vertex>& theVtx1, 
	const std::shared_ptr<TModel_Curve>& theCurve, 
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: TModel_Entity(theIndex)
	, TModel_EdgeGeometry(theCurve, theParaCurve, theSense)
	, theVtx0_(theVtx0)
	, theVtx1_(theVtx1)
{
}

tnbLib::TModel_Edge::TModel_Edge
(
	const Standard_Integer theIndex,
	const std::shared_ptr<TModel_Curve>& theCurve,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: TModel_EdgeGeometry(theCurve, theParaCurve, theSense)
	, TModel_Entity(theIndex)
{
}

tnbLib::TModel_Edge::TModel_Edge
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<TModel_Vertex>& theVtx0,
	const std::shared_ptr<TModel_Vertex>& theVtx1,
	const std::shared_ptr<TModel_Curve>& theCurve,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: TModel_Entity(theIndex, theName)
	, TModel_EdgeGeometry(theCurve, theParaCurve, theSense)
	, theVtx0_(theVtx0)
	, theVtx1_(theVtx1)
{
}

tnbLib::TModel_Edge::TModel_Edge
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<TModel_Curve>& theCurve,
	const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: TModel_EdgeGeometry(theCurve, theParaCurve, theSense)
	, TModel_Entity(theIndex, theName)
{
}