#include <Marine_Section_Water.hxx>

#include <Pln_Wire.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Marine_SectTools.hxx>
#include <Pln_Wire.hxx>

void tnbLib::marineLib::Section_Water::CheckCurves() const
{
	Debug_Null_Pointer(Wire());
	const auto& curves = Wire()->RetrieveCurves();
	for (const auto& x : curves)
	{
		if (NOT Marine_SectTools::IsWater(x))
		{
			FatalErrorIn(FunctionSIG)
				<< " the curve is supposed to be a water!" << endl
				<< abort(FatalError);
		}
	}
}


tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Water>::OuterSection
(
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Section_Water(theWire)
{
	// empty body
}

tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Water>::OuterSection
(
	std::shared_ptr<Pln_Wire>&& theWire
)
	: Section_Water(std::move(theWire))
{
	// empty body
}

tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Water>::OuterSection
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Section_Water(theIndex, theWire)
{
	// empty body
}

tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Water>::OuterSection
(
	const Standard_Integer theIndex, 
	std::shared_ptr<Pln_Wire>&& theWire
)
	: Section_Water(theIndex, std::move(theWire))
{
	// empty body
}

tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Water>::OuterSection
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Section_Water(theIndex, theName, theWire)
{
	// empty body
}

tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Water>::OuterSection
(
	const Standard_Integer theIndex,
	const word & theName, 
	std::shared_ptr<Pln_Wire>&& theWire
)
	: Section_Water(theIndex, theName, std::move(theWire))
{
	// empty body
}

std::shared_ptr<tnbLib::Marine_Section>
tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Water>::Copy() const
{
	auto wire = std::dynamic_pointer_cast<Pln_Wire>(Wire()->Copy());
	Debug_Null_Pointer(wire);

	auto copy = std::make_shared<OuterSection<Section_Water>>(Index(), Name(), wire);
	Debug_Null_Pointer(copy);

	return std::move(copy);
}