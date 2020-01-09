#include <pairGAMGAgglomeration.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pairGAMGAgglomeration, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pairGAMGAgglomeration::pairGAMGAgglomeration
(
	const lduMesh& mesh,
	const dictionary& dict
)
	:
	GAMGAgglomeration(mesh, dict),
	mergeLevels_(readLabel(dict.lookup("mergeLevels")))
{}


// ************************************************************************* //