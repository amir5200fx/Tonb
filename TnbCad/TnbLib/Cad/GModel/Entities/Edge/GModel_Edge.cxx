#include <GModel_Edge.hxx>

tnbLib::GModel_Edge::GModel_Edge
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<GModel_ParaCurve>& thePar, 
	const std::shared_ptr<GModel_Curve>& theCurve
)
	: GModel_Entity(theIndex)
	, thePar_(thePar)
	, theCurve_(theCurve)
{
}

tnbLib::GModel_Edge::GModel_Edge
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<GModel_ParaCurve>& thePar,
	const std::shared_ptr<GModel_Curve>& theCurve
)
	: GModel_Entity(theIndex, theName)
	, thePar_(thePar)
	, theCurve_(theCurve)
{
}