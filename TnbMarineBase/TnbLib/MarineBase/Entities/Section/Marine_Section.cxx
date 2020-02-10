#include <Marine_Section.hxx>

#include <error.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::Marine_Section::GetXcoord
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	Debug_Null_Pointer(theSection);
	return theSection->CoordinateSystem().Location().X();
}