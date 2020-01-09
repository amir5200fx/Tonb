#include <regionCoupleAMGInterface.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regionCoupleAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		AMGInterface,
		regionCoupleAMGInterface,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionCoupleAMGInterface::regionCoupleAMGInterface
(
	const lduPrimitiveMesh& lduMesh,
	const lduInterface& fineInterface,
	const labelField& localRestrictAddressing,
	const labelField& neighbourRestrictAddressing
)
	:
	ggiAMGInterface
	(
		lduMesh,
		fineInterface,
		localRestrictAddressing,
		neighbourRestrictAddressing
	),
	coupled_(fineInterface.coupled())
{}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

tnbLib::regionCoupleAMGInterface::~regionCoupleAMGInterface()
{}


// ************************************************************************* //
