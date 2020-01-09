#include <blockLduSolvers.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineNamedTemplateTypeNameAndDebug(blockScalarSolver, 0);
	defineNamedTemplateTypeNameAndDebug(blockVectorSolver, 0);
	defineNamedTemplateTypeNameAndDebug(blockTensorSolver, 0);


	// Define the constructor function hash tables for symmetric solvers

	defineTemplateRunTimeSelectionTable
	(
		blockScalarSolver,
		symMatrix
	);

	defineTemplateRunTimeSelectionTable
	(
		blockVectorSolver,
		symMatrix
	);

	defineTemplateRunTimeSelectionTable
	(
		blockTensorSolver,
		symMatrix
	);


	// Define the constructor function hash tables for asymmetric solvers

	defineTemplateRunTimeSelectionTable
	(
		blockScalarSolver,
		asymMatrix
	);

	defineTemplateRunTimeSelectionTable
	(
		blockVectorSolver,
		asymMatrix
	);

	defineTemplateRunTimeSelectionTable
	(
		blockTensorSolver,
		asymMatrix
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //