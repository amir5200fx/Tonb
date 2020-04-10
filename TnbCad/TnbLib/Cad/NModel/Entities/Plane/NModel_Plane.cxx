#include <NModel_Plane.hxx>

tnbLib::NModel_Plane::NModel_Plane
(
	const outer & theOuter,
	const inner & theInner,
	const std::shared_ptr<curveList>& theCurves
)
	: theOutter_(theOuter)
	, theInner_(theInner)
	, theCurves_(theCurves)
{
}

tnbLib::NModel_Plane::NModel_Plane
(
	const Standard_Integer theIndex,
	const outer & theOuter,
	const inner & theInner,
	const std::shared_ptr<curveList>& theCurves
)
	: theOutter_(theOuter)
	, theInner_(theInner)
	, theCurves_(theCurves)
	, NModel_Entity(theIndex)
{
}

tnbLib::NModel_Plane::NModel_Plane
(
	const Standard_Integer theIndex,
	const word& theName,
	const outer & theOuter,
	const inner & theInner,
	const std::shared_ptr<curveList>& theCurves
)
	: theOutter_(theOuter)
	, theInner_(theInner)
	, theCurves_(theCurves)
	, NModel_Entity(theIndex, theName)
{
}

Standard_Integer
tnbLib::NModel_Plane::NbHoles() const
{
	if (HasHole())
	{
		return (Standard_Integer)Holes()->size();
	}
	return 0;
}

typename tnbLib::NModel_Plane::wireList
tnbLib::NModel_Plane::RetrieveWires() const
{
	wireList wires;
	RetrieveWiresTo(wires);

	return std::move(wires);
}

void tnbLib::NModel_Plane::RetrieveWiresTo
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