#include <GModel_Surface.hxx>

tnbLib::GModel_Surface::GModel_Surface
(
	const Handle(Geom_Surface)& theGeometry,
	const outer & theOuter,
	const inner & theInner
)
	: GModel_SurfaceGeometry(theGeometry)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
}

tnbLib::GModel_Surface::GModel_Surface
(
	const Standard_Integer theIndex,
	const Handle(Geom_Surface)& theGeometry,
	const outer & theOuter,
	const inner & theInner
)
	: GModel_SurfaceGeometry(theGeometry)
	, GModel_Entity(theIndex)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
}

tnbLib::GModel_Surface::GModel_Surface
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom_Surface)& theGeometry,
	const outer & theOuter,
	const inner & theInner
)
	: GModel_SurfaceGeometry(theGeometry)
	, GModel_Entity(theIndex, theName)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
}

Standard_Integer
tnbLib::GModel_Surface::NbHoles() const
{
	if (NOT theInner_) return 0;
	return (Standard_Integer)theInner_->size();
}

Standard_Boolean
tnbLib::GModel_Surface::HasHole() const
{
	return NbHoles();
}

