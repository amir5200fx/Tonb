#include <blockAMGSolvers.hxx>

#include <blockLduMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	// Excluded tensor: needs reduced version.  HJ, 28/May/2014

	makeBlockSolverTypeName(blockAmgSolverScalar);
	makeBlockSolverTypeName(blockAmgSolverVector);
	// makeBlockSolvers(blockAmgSolver);

	addSolverToBlockMatrix(Scalar, blockAmgSolverScalar, symMatrix);
	addSolverToBlockMatrix(Vector, blockAmgSolverVector, symMatrix);
	// addSymSolverToBlockMatrix(blockAmgSolver);

	addSolverToBlockMatrix(Scalar, blockAmgSolverScalar, asymMatrix);
	addSolverToBlockMatrix(Vector, blockAmgSolverVector, asymMatrix);
	// addAsymSolverToBlockMatrix(blockAmgSolver);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //