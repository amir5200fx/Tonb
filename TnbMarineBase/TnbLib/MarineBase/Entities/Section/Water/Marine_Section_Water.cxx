#include <Marine_Section_Water.hxx>

#include <Pln_Wire.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::Marine_Section>
tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Water>::Copy() const
{
	auto wire = std::dynamic_pointer_cast<Pln_Wire>(Wire()->Copy());
	Debug_Null_Pointer(wire);

	auto copy = std::make_shared<OuterSection<Section_Water>>(Index(), Name(), wire);
	Debug_Null_Pointer(copy);

	return std::move(copy);
}