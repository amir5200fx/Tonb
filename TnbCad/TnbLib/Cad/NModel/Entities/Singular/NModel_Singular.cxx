#include <NModel_Singular.hxx>

tnbLib::NModel_SingularEdge::NModel_SingularEdge
(
	const std::shared_ptr<NModel_Vertex>& theVtx,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve
)
	: NModel_Edge(theVtx, theVtx, nullptr, theParaCurve, Standard_True)
{
}

tnbLib::NModel_SingularEdge::NModel_SingularEdge
(
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve
)
	: NModel_Edge(nullptr, theParaCurve)
{
}

tnbLib::NModel_SingularEdge::NModel_SingularEdge
(
	const Standard_Integer theIndex,
	const std::shared_ptr<NModel_Vertex>& theVtx,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve
)
	: NModel_Edge(theIndex, theVtx, theVtx, nullptr, theParaCurve)
{
}

tnbLib::NModel_SingularEdge::NModel_SingularEdge
(
	const Standard_Integer theIndex,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve
)
	: NModel_Edge(theIndex, nullptr, theParaCurve)
{
}

tnbLib::NModel_SingularEdge::NModel_SingularEdge
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<NModel_Vertex>& theVtx,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve
)
	: NModel_Edge(theIndex, theName, theVtx, theVtx, nullptr, theParaCurve)
{
}

tnbLib::NModel_SingularEdge::NModel_SingularEdge
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<NModel_ParaCurve>& theParaCurve
)
	: NModel_Edge(theIndex, theName, nullptr, theParaCurve)
{
}