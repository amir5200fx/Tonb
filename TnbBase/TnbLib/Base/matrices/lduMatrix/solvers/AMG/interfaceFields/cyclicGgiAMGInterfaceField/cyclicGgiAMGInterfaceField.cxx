#include <cyclicGgiAMGInterfaceField.hxx>

#include <lduMatrix.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicGgiAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		AMGInterfaceField,
		cyclicGgiAMGInterfaceField,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicGgiAMGInterfaceField::cyclicGgiAMGInterfaceField
(
	const AMGInterface& AMGCp,
	const lduInterfaceField& fineInterface
)
	:
	ggiAMGInterfaceField(AMGCp, fineInterface)
{}


// * * * * * * * * * * * * * * * * Desstructor * * * * * * * * * * * * * * * //

tnbLib::cyclicGgiAMGInterfaceField::~cyclicGgiAMGInterfaceField()
{}


// ************************************************************************* //