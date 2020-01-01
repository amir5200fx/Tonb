#include <intersection.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

//tnbLib::debug::controlSwitches<tnbLib::scalar>
tnbLib::debug::tolerancesSwitch
tnbLib::intersection::planarTol_
(
	"intersectionPlanarTol",
	0.2
);

//const tnbLib::debug::controlSwitches<tnbLib::scalar>
const tnbLib::debug::tolerancesSwitch
tnbLib::intersection::missTol_
(
	"intersectionMissTol",
	SMALL
);

template<>
const char* tnbLib::NamedEnum<tnbLib::intersection::direction, 2>::names[] =
{
	"vector",
	"contactSphere"
};


const tnbLib::NamedEnum<tnbLib::intersection::direction, 2>
tnbLib::intersection::directionNames_;


template<>
const char* tnbLib::NamedEnum<tnbLib::intersection::algorithm, 3>::names[] =
{
	"fullRay",
	"halfRay",
	"visible"
};


const tnbLib::NamedEnum<tnbLib::intersection::algorithm, 3>
tnbLib::intersection::algorithmNames_;



// ************************************************************************* //