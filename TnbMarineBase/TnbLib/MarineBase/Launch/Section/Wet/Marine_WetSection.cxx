#include <Marine_WetSection.hxx>

tnbLib::Marine_WetSection::Marine_WetSection
(
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Marine_Section(theWire)
{
}

tnbLib::Marine_WetSection::Marine_WetSection
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Marine_Section(theIndex, theWire)
{
}

tnbLib::Marine_WetSection::Marine_WetSection
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Marine_Section(theIndex, theName, theWire)
{
}