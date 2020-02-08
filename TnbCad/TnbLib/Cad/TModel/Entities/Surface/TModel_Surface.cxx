#include <TModel_Surface.hxx>

#include <TModel_Edge.hxx>
#include <TModel_CmpEdge.hxx>
#include <TModel_Wire.hxx>

tnbLib::TModel_Surface::TModel_Surface
(
	const Handle(Geom_Surface)& theGeometry, 
	const outer & theOuter,
	const inner & theInner
)
	: TModel_SurfaceGeometry(theGeometry)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
}

tnbLib::TModel_Surface::TModel_Surface
(
	const Standard_Integer theIndex,
	const Handle(Geom_Surface)& theGeometry,
	const outer & theOuter,
	const inner & theInner
)
	: TModel_SurfaceGeometry(theGeometry)
	, TModel_Entity(theIndex)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
}

tnbLib::TModel_Surface::TModel_Surface
(
	const Standard_Integer theIndex,
	const word& theName,
	const Handle(Geom_Surface)& theGeometry,
	const outer & theOuter,
	const inner & theInner
)
	: TModel_SurfaceGeometry(theGeometry)
	, TModel_Entity(theIndex, theName)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
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

Standard_Boolean 
tnbLib::TModel_Surface::IsClamped() const
{
	Debug_Null_Pointer(theOuter_);
	Debug_Null_Pointer(theOuter_->CmpEdge());

	const auto& cmpEdge = *theOuter_->CmpEdge();
	for (const auto& x : cmpEdge.Edges())
	{
		Debug_Null_Pointer(x);
		if (NOT x->PairedEdge().lock()) return Standard_False;
	}
	return Standard_True;
}

std::vector<std::shared_ptr<tnbLib::TModel_Edge>> 
tnbLib::TModel_Surface::RetrieveEdges() const
{
	if (NOT theOuter_)
	{
		FatalErrorIn("std::vector<std::shared_ptr<TModel_Edge>> Edges() const")
			<< "Invalid Surface: There is no outer wire for the surface" << endl
			<< abort(FatalError);
	}

	auto size = theOuter_->CmpEdge()->NbEdges();
	if (theInner_)
	{
		for (const auto& x : *theInner_)
		{
			size += x->CmpEdge()->NbEdges();
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

	Debug_Null_Pointer(theOuter_->CmpEdge());
	const auto& OuterEdges = theOuter_->CmpEdge()->Edges();

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
		Debug_Null_Pointer(x->CmpEdge());
		for (const auto& edge : x->CmpEdge()->Edges())
		{
			edges.push_back(edge);
		}
	}
	return std::move(edges);
}