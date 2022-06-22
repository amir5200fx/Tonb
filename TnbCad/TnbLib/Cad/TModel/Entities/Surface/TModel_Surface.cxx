#include <TModel_Surface.hxx>

#include <TModel_Tools.hxx>
#include <TModel_Edge.hxx>
#include <TModel_CmpEdge.hxx>
#include <TModel_Wire.hxx>

tnbLib::Entity2d_Box 
tnbLib::TModel_Surface::CalcParametricBoundingBox() const
{
	auto wire = TModel_Wire::RetrieveParaWire(*theOuter_);
	auto box = TModel_Tools::CalcBoundingBox(*wire);
	return std::move(box);
}

tnbLib::TModel_Surface::TModel_Surface
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

tnbLib::TModel_Surface::TModel_Surface
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

tnbLib::TModel_Surface::TModel_Surface
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Cad_GeomSurface>& theGeometry,
	const outer & theOuter,
	const inner & theInner
)
	: GModel_SurfaceGeometry(theGeometry)
	, TModel_Entity(theIndex)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
	theParaBoundingBox_ = CalcParametricBoundingBox();
}

tnbLib::TModel_Surface::TModel_Surface
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<Cad_GeomSurface>& theGeometry,
	const outer & theOuter,
	const inner & theInner
)
	: GModel_SurfaceGeometry(theGeometry)
	, TModel_Entity(theIndex, theName)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
	theParaBoundingBox_ = CalcParametricBoundingBox();
}

Standard_Integer 
tnbLib::TModel_Surface::NbHoles() const
{
	if (NOT theInner_) return 0;
	return (Standard_Integer)theInner_->size();
}

Standard_Boolean 
tnbLib::TModel_Surface::HasHole() const
{
	return NbHoles();
}

//Standard_Boolean 
//tnbLib::TModel_Surface::IsClamped() const
//{
//	Debug_Null_Pointer(theOuter_);
//	Debug_Null_Pointer(theOuter_->CmpEdge());
//
//	const auto& cmpEdge = *theOuter_->CmpEdge();
//	for (const auto& x : cmpEdge.Edges())
//	{
//		Debug_Null_Pointer(x);
//		if (NOT x->PairedEdge().lock()) return Standard_False;
//	}
//	return Standard_True;
//}

std::vector<std::shared_ptr<tnbLib::TModel_Edge>> 
tnbLib::TModel_Surface::RetrieveEdges() const
{
	if (NOT theOuter_)
	{
		FatalErrorIn("std::vector<std::shared_ptr<TModel_Edge>> Edges() const")
			<< "Invalid Surface: There is no outer wire for the surface" << endl
			<< abort(FatalError);
	}

	auto size = theOuter_->NbEdges();
	if (theInner_)
	{
		for (const auto& x : *theInner_)
		{
			size += x->NbEdges();
		}
	}

	if (NOT size)
	{
		FatalErrorIn("std::vector<std::shared_ptr<TModel_Edge>> Edges() const")
			<< "Invalid Surface: the surface has no edge" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<TModel_Edge>> edges;
	edges.reserve(size);

	Debug_Null_Pointer(theOuter_->Edges());
	const auto& OuterEdges = *theOuter_->Edges();

	for (const auto& x : OuterEdges)
	{
		edges.push_back(x);
	}

	if (NOT theInner_)
	{
		return std::move(edges);
	}

	for (const auto& x : *theInner_)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Edges());
		for (const auto& edge : *x->Edges())
		{
			edges.push_back(edge);
		}
	}
	return std::move(edges);
}