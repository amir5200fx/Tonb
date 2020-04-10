#include <NModel_Ring.hxx>

tnbLib::NModel_Ring::NModel_Ring
(
	const std::shared_ptr<NModel_Vertex>& theVtx,
	const std::shared_ptr<NModel_Curve>& theCurve,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: NModel_Edge(theVtx, theVtx, theCurve, theParaCurve, theSense)
{
}

tnbLib::NModel_Ring::NModel_Ring
(
	const Standard_Integer theIndex,
	const std::shared_ptr<NModel_Vertex>& theVtx,
	const std::shared_ptr<NModel_Curve>& theCurve,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: NModel_Edge(theIndex, theVtx, theVtx, theCurve, theParaCurve, theSense)
{
}

tnbLib::NModel_Ring::NModel_Ring
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<NModel_Vertex>& theVtx,
	const std::shared_ptr<NModel_Curve>& theCurve,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: NModel_Edge(theIndex, theName, theVtx, theVtx, theCurve, theParaCurve, theSense)
{
}

tnbLib::NModel_Ring::NModel_Ring
(
	const std::shared_ptr<NModel_Curve>& theCurve,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: NModel_Edge(theCurve, theParaCurve, theSense)
{
}

tnbLib::NModel_Ring::NModel_Ring
(
	const Standard_Integer theIndex,
	const std::shared_ptr<NModel_Curve>& theCurve,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: NModel_Edge(theIndex, theCurve, theParaCurve, theSense)
{
}

tnbLib::NModel_Ring::NModel_Ring
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<NModel_Curve>& theCurve,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
	const Standard_Boolean theSense
)
	: NModel_Edge(theIndex, theName, theCurve, theParaCurve, theSense)
{
}