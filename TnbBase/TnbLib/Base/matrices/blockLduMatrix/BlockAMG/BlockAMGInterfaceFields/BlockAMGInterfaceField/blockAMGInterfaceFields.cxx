#include <blockAMGInterfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineNamedTemplateTypeNameAndDebug(blockScalarAMGInterfaceField, 0);
	defineNamedTemplateTypeNameAndDebug(blockVectorAMGInterfaceField, 0);
	defineNamedTemplateTypeNameAndDebug(blockTensorAMGInterfaceField, 0);

	defineTemplateRunTimeSelectionTable
	(
		blockScalarAMGInterfaceField,
		lduInterface
	);

	defineTemplateRunTimeSelectionTable
	(
		blockVectorAMGInterfaceField,
		lduInterface
	);

	defineTemplateRunTimeSelectionTable
	(
		blockTensorAMGInterfaceField,
		lduInterface
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //