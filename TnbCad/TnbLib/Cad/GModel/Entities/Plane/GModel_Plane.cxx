#include <GModel_Plane.hxx>

tnbLib::GModel_Plane::GModel_Plane
(
	const outer & theOuter,
	const inner & theInner
)
	: theOuter_(theOuter)
	, theInner_(theInner)
{
	//- empty body
}

tnbLib::GModel_Plane::GModel_Plane
(
	const Standard_Integer theIndex,
	const outer & theOuter, 
	const inner & theInner
)
	: Global_Indexed(theIndex)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
	//- empty body
}

tnbLib::GModel_Plane::GModel_Plane
(
	const Standard_Integer theIndex, 
	const word & theName,
	const outer & theOuter, 
	const inner & theInner
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
	//- empty body
}

Standard_Boolean 
tnbLib::GModel_Plane::HasHole() const
{
	return (Standard_Boolean)theInner_;
}

Standard_Integer 
tnbLib::GModel_Plane::NbHoles() const
{
	if (NOT HasHole())
	{
		return Standard_False;
	}
	return (Standard_Integer)theInner_->size();
}