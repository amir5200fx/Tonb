#include <blockCoeffBase.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* tnbLib::NamedEnum<tnbLib::blockCoeffBase::activeLevel, 4>::names[] =
{
	"unallocated",
	"scalar",
	"linear",
	"square"
};

const tnbLib::NamedEnum<tnbLib::blockCoeffBase::activeLevel, 4>
tnbLib::blockCoeffBase::activeLevelNames_;


// ************************************************************************* //