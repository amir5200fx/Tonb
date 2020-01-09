#include <algebraicPairGAMGAgglomeration.hxx>

#include <lduMatrix.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(algebraicPairGAMGAgglomeration, 0);

	addToRunTimeSelectionTable
	(
		GAMGAgglomeration,
		algebraicPairGAMGAgglomeration,
		lduMatrix
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::algebraicPairGAMGAgglomeration::algebraicPairGAMGAgglomeration
(
	const lduMatrix& matrix,
	const dictionary& dict
)
	:
	pairGAMGAgglomeration(matrix.mesh(), dict)
{
	agglomerate(matrix.mesh(), mag(matrix.upper()));
}


// ************************************************************************* //