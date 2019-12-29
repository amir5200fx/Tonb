#include <bool.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

const char* const tnbLib::pTraits<bool>::typeName = "bool";
const bool tnbLib::pTraits<bool>::zero(false);
const bool tnbLib::pTraits<bool>::one(true);

const char* tnbLib::pTraits<bool>::componentNames[] = { "x" };

tnbLib::pTraits<bool>::pTraits(Istream& is)
{
	is >> p_;
}

// ************************************************************************* //