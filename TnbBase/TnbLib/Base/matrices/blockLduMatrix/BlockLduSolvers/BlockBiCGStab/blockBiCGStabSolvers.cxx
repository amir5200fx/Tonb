#include <blockBiCGStabSolvers.hxx>

#include <blockLduMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makeBlockSolvers(blockBiCGStabSolver);

	// BiCGStab as a symmetric solver: use where the diagonal coefficient block
	// is assymetric.  HJ, 24/Jan/2008
	addSymSolverToBlockMatrix(blockBiCGStabSolver);

	addAsymSolverToBlockMatrix(blockBiCGStabSolver);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //