#include <blockLduMatrices.hxx>
#include <blockLduPrecons.hxx>
#include <blockAMGPrecons.hxx>
#include <addToRunTimeSelectionTable.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	// Excluded tensor: needs reduced version.  HJ, 28/May/2014
	makeBlockPrecon(blockScalarPrecon, blockAMGPreconScalar);
	makeBlockPrecon(blockVectorPrecon, blockAMGPreconVector);
	// makeBlockPrecons(blockAMGPrecon);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //