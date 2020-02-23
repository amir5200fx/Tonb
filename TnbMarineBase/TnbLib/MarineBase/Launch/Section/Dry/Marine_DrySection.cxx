#include <Marine_DrySection.hxx>

tnbLib::Marine_DrySection::Marine_DrySection
(
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Marine_Section(theWire)
{
}

tnbLib::Marine_DrySection::Marine_DrySection
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Marine_Section(theIndex, theWire)
{
}

tnbLib::Marine_DrySection::Marine_DrySection
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Marine_Section(theIndex, theName, theWire)
{
}