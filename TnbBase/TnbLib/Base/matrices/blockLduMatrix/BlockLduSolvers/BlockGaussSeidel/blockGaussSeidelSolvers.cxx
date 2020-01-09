#include <blockGaussSeidelSolvers.hxx>

#include <blockLduMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makeBlockSolvers(blockGaussSeidelSolver);

	addSymSolverToBlockMatrix(blockGaussSeidelSolver);

	addAsymSolverToBlockMatrix(blockGaussSeidelSolver);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //