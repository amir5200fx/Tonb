#include <IOMap.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //
namespace tnbLib
{
	template <>
	const ::tnbLib::word IOMap<dictionary>::typeName("IOMap<dictionary>");
	template <>
	::tnbLib::debug::debugSwitch IOMap<dictionary>::debug(std::string("IOMap<dictionary>"), 0, "");;
}

// ************************************************************************* //