#include <segregatedSolvers.hxx>

#include <blockLduMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	// Segregated scalar solver makes no sense and is not instantiated
	makeBlockSolverTypeName(segregatedSolverVector);
	makeBlockSolverTypeName(segregatedSolverTensor);

	addSolverToBlockMatrix(Vector, segregatedSolverVector, symMatrix);
	addSolverToBlockMatrix(Tensor, segregatedSolverTensor, symMatrix);

	addSolverToBlockMatrix(Vector, segregatedSolverVector, asymMatrix);
	addSolverToBlockMatrix(Tensor, segregatedSolverTensor, asymMatrix);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //