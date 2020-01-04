#include <GGIInterpolationTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::GGIInterpolationName, 0);


template<>
const char*
tnbLib::NamedEnum<tnbLib::GGIInterpolationName::quickReject, 3>::names[] =
{
	"distance3D",
	"AABB",
	"bbOctree"
};


const tnbLib::NamedEnum<tnbLib::GGIInterpolationName::quickReject, 3>
tnbLib::GGIInterpolationName::quickRejectNames_;


// ************************************************************************* //