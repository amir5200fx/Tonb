#include <cyclicGGIAMGInterface.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicGGIAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		AMGInterface,
		cyclicGGIAMGInterface,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicGGIAMGInterface::cyclicGGIAMGInterface
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
	)
{}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

tnbLib::cyclicGGIAMGInterface::~cyclicGGIAMGInterface()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


// ************************************************************************* //