#include <blockGaussSeidelPrecons.hxx>

#include <blockLduMatrices.hxx>
#include <blockLduPrecons.hxx>
#include <addToRunTimeSelectionTable.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makeBlockPrecons(blockGaussSeidelPrecon);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //