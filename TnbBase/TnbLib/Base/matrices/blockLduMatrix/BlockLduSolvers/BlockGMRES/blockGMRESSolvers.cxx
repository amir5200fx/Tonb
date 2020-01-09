#include <blockGMRESSolvers.hxx>

#include <blockLduMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makeBlockSolvers(blockGMRESsolver);

	addSymSolverToBlockMatrix(blockGMRESsolver);
	addAsymSolverToBlockMatrix(blockGMRESsolver);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //