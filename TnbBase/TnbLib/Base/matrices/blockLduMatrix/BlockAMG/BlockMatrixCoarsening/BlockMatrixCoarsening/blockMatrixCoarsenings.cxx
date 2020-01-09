#include <blockMatrixCoarsenings.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineNamedTemplateTypeNameAndDebug(blockScalarMatrixCoarsening, 0);
	defineNamedTemplateTypeNameAndDebug(blockVectorMatrixCoarsening, 0);
	defineNamedTemplateTypeNameAndDebug(blockTensorMatrixCoarsening, 0);

	defineTemplateRunTimeSelectionTable
	(
		blockScalarMatrixCoarsening,
		matrix
	);

	defineTemplateRunTimeSelectionTable
	(
		blockVectorMatrixCoarsening,
		matrix
	);

	defineTemplateRunTimeSelectionTable
	(
		blockTensorMatrixCoarsening,
		matrix
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //