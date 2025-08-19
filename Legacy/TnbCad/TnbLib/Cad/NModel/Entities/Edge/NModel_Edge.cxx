#include <NModel_Edge.hxx>

tnbLib::NModel_Edge::NModel_Edge
(
	const std::shared_ptr<NModel_Vertex>& theVtx0,
	const std::shared_ptr<NModel_Vertex>& theVtx1,
	const std::shared_ptr<NModel_Curve>& theCurve,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: NModel_EdgeGeometry(theCurve, theParaCurve, theSense)
	, theVtx0_(theVtx0)
	, theVtx1_(theVtx1)
{
}

tnbLib::NModel_Edge::NModel_Edge
(
	const std::shared_ptr<NModel_Curve>& theCurve,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: NModel_EdgeGeometry(theCurve, theParaCurve, theSense)
{
}

tnbLib::NModel_Edge::NModel_Edge
(
	const Standard_Integer theIndex,
	const std::shared_ptr<NModel_Vertex>& theVtx0,
	const std::shared_ptr<NModel_Vertex>& theVtx1,
	const std::shared_ptr<NModel_Curve>& theCurve,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: NModel_Entity(theIndex)
	, NModel_EdgeGeometry(theCurve, theParaCurve, theSense)
	, theVtx0_(theVtx0)
	, theVtx1_(theVtx1)
{
}

tnbLib::NModel_Edge::NModel_Edge
(
	const Standard_Integer theIndex,
	const std::shared_ptr<NModel_Curve>& theCurve,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: NModel_EdgeGeometry(theCurve, theParaCurve, theSense)
	, NModel_Entity(theIndex)
{
}

tnbLib::NModel_Edge::NModel_Edge
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<NModel_Vertex>& theVtx0,
	const std::shared_ptr<NModel_Vertex>& theVtx1,
	const std::shared_ptr<NModel_Curve>& theCurve,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: NModel_Entity(theIndex, theName)
	, NModel_EdgeGeometry(theCurve, theParaCurve, theSense)
	, theVtx0_(theVtx0)
	, theVtx1_(theVtx1)
{
}

tnbLib::NModel_Edge::NModel_Edge
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<NModel_Curve>& theCurve,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: NModel_EdgeGeometry(theCurve, theParaCurve, theSense)
	, NModel_Entity(theIndex, theName)
{
}