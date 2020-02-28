#include <Marine_DrySection.hxx>

#include <Pln_Wire.hxx>
#include <error.hxx>
#include <OSstream.hxx>

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

std::shared_ptr<tnbLib::Marine_Section> 
tnbLib::Marine_DrySection::Copy() const
{
	auto wire = std::dynamic_pointer_cast<Pln_Wire>(Wire()->Copy());
	Debug_Null_Pointer(wire);

	auto copy = std::make_shared<Marine_DrySection>(Index(), Name(), wire);
	Debug_Null_Pointer(copy);

	return std::move(copy);
}