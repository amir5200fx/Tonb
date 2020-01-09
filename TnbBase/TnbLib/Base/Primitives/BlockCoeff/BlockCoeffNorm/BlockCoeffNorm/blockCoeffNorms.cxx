#include <blockCoeffNorms.hxx>
#include <BlockCoeffNorm.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineNamedTemplateTypeNameAndDebug(blockScalarCoeffNorm, 0);
	defineNamedTemplateTypeNameAndDebug(blockVectorCoeffNorm, 0);
	defineNamedTemplateTypeNameAndDebug(blockTensorCoeffNorm, 0);

	// Define the constructor function hash tables for symmetric solvers

	defineTemplateRunTimeSelectionTable
	(
		blockScalarCoeffNorm,
		dictionary
	);

	defineTemplateRunTimeSelectionTable
	(
		blockVectorCoeffNorm,
		dictionary
	);

	defineTemplateRunTimeSelectionTable
	(
		blockTensorCoeffNorm,
		dictionary
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //