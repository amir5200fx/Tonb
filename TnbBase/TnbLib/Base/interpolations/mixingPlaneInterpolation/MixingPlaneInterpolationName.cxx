#include <MixingPlaneInterpolationTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::MixingPlaneInterpolationName, 0);

template<>
const char*
tnbLib::NamedEnum
<
	tnbLib::MixingPlaneInterpolationName::discretisation,
	5
>::names[] =
{
	"masterPatch",
	"slavePatch",
	"bothPatches",
	"uniform",
	"userDefined"
};


const tnbLib::NamedEnum
<
	tnbLib::MixingPlaneInterpolationName::discretisation,
	5
>
tnbLib::MixingPlaneInterpolationName::discretisationNames_;


template<>
const char*
tnbLib::NamedEnum
<
	tnbLib::MixingPlaneInterpolationName::sweepAxis,
	6
>::names[] =
{
	"X",
	"Y",
	"Z",
	"R",
	"Theta",
	"Unknown"
};


const tnbLib::NamedEnum
<
	tnbLib::MixingPlaneInterpolationName::sweepAxis,
	6
>
tnbLib::MixingPlaneInterpolationName::sweepAxisNames_;

template<>
const char*
tnbLib::NamedEnum
<
	tnbLib::MixingPlaneInterpolationName::stackAxis,
	6
>::names[] =
{
	"X",
	"Y",
	"Z",
	"R",
	"Theta",
	"Unknown"
};


const tnbLib::NamedEnum
<
	tnbLib::MixingPlaneInterpolationName::stackAxis,
	6
>
tnbLib::MixingPlaneInterpolationName::stackAxisNames_;


template<>
const char*
tnbLib::NamedEnum
<
	tnbLib::MixingPlaneInterpolationName::mixingType,
	6
>::names[] =
{
	"areaAveraging",
	"fluxAveraging",
	"uniformValue",
	"uniformGradient",
	"zeroGradient",
	"unknown"
};


const tnbLib::NamedEnum
<
	tnbLib::MixingPlaneInterpolationName::mixingType,
	6
>
tnbLib::MixingPlaneInterpolationName::mixingTypeNames_;


// ************************************************************************* //