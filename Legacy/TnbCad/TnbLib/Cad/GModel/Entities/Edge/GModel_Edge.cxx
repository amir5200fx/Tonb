#include <GModel_Edge.hxx>

tnbLib::GModel_Edge::GModel_Edge
(
	const std::shared_ptr<GModel_ParaCurve>& thePar, 
	const std::shared_ptr<GModel_Curve>& theCurve
)
	: thePar_(thePar)
	, theCurve_(theCurve)
{
	//- empty body
}

tnbLib::GModel_Edge::GModel_Edge
(
	std::shared_ptr<GModel_ParaCurve>&& thePar,
	std::shared_ptr<GModel_Curve>&& theCurve
)
	: thePar_(std::move(thePar))
	, theCurve_(std::move(theCurve))
{
	//- empty body
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
	//- empty body
}