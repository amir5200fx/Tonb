#include <GModel_Surface.hxx>

tnbLib::GModel_Surface::GModel_Surface
(
	const std::shared_ptr<Cad_GeomSurface>& theGeometry,
	const outer & theOuter,
	const inner & theInner
)
	: GModel_SurfaceGeometry(theGeometry)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
	//- empty body
}

tnbLib::GModel_Surface::GModel_Surface
(
	std::shared_ptr<Cad_GeomSurface>&& theGeometry, 
	outer && theOuter,
	inner && theInner
)
	: GModel_SurfaceGeometry(std::move(theGeometry))
	, theOuter_(std::move(theOuter))
	, theInner_(std::move(theInner))
{
	//- empty body
}

tnbLib::GModel_Surface::GModel_Surface
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Cad_GeomSurface>& theGeometry,
	const outer & theOuter,
	const inner & theInner
)
	: GModel_SurfaceGeometry(theGeometry)
	, GModel_Entity(theIndex)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
	//- empty body
}

tnbLib::GModel_Surface::GModel_Surface
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<Cad_GeomSurface>& theGeometry,
	const outer & theOuter,
	const inner & theInner
)
	: GModel_SurfaceGeometry(theGeometry)
	, GModel_Entity(theIndex, theName)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
	//- empty body
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

