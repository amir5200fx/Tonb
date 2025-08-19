#include <GModel_Surface.hxx>

#include <GModel_Tools.hxx>
#include <GModel_Wire.hxx>

tnbLib::Entity2d_Box 
tnbLib::GModel_Surface::CalcParametricBoundingBox() const
{
	auto wire = GModel_Wire::RetrieveParaWire(*theOuter_);
	auto box = GModel_Tools::CalcBoundingBox(*wire);
	return std::move(box);
}

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
	theParaBoundingBox_ = CalcParametricBoundingBox();
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
	theParaBoundingBox_ = CalcParametricBoundingBox();
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
	theParaBoundingBox_ = CalcParametricBoundingBox();
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
	theParaBoundingBox_ = CalcParametricBoundingBox();
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

std::vector<std::shared_ptr<tnbLib::GModel_Edge>>
tnbLib::GModel_Surface::RetrieveEdges() const
{
	if (NOT theOuter_)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Invalid surface." << endl
			<< abort(FatalError);
	}
	std::vector<std::shared_ptr<GModel_Edge>> edges;
	for (const auto& e: *theOuter_->Edges())
	{
		edges.emplace_back(e);
	}
	if (theInner_)
	{
		for (const auto& wire: *theInner_)
		{
			for (const auto& e: *wire->Edges())
			{
				edges.emplace_back(e);
			}
		}
	}
	return std::move(edges);
}

