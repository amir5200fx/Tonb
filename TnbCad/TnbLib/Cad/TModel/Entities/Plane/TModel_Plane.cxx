#include <TModel_Plane.hxx>

tnbLib::TModel_Plane::TModel_Plane
(
	const outer & theOuter, 
	const inner & theInner
)
	: theOuter_(theOuter)
	, theInner_(theInner)
{
}

tnbLib::TModel_Plane::TModel_Plane
(
	const Standard_Integer theIndex,
	const outer & theOuter,
	const inner & theInner
)
	: theOuter_(theOuter)
	, theInner_(theInner)
	, TModel_Entity(theIndex)
{
}

tnbLib::TModel_Plane::TModel_Plane
(
	const Standard_Integer theIndex,
	const word& theName,
	const outer & theOuter,
	const inner & theInner
)
	: theOuter_(theOuter)
	, theInner_(theInner)
	, TModel_Entity(theIndex, theName)
{
}

Standard_Integer 
tnbLib::TModel_Plane::NbHoles() const
{
	if (HasHole())
	{
		return (Standard_Integer)Holes()->size();
	}
	return 0;
}

typename tnbLib::TModel_Plane::wireList 
tnbLib::TModel_Plane::RetrieveWires() const
{
	wireList wires;
	RetrieveWiresTo(wires);

	return std::move(wires);
}

void tnbLib::TModel_Plane::RetrieveWiresTo
(
	wireList & theWires
) const
{
	theWires.reserve(1 + NbHoles());
	theWires.push_back(Outer());

	if (Holes())
	{
		for (const auto& x : *Holes())
		{
			theWires.push_back(x);
		}
	}
}