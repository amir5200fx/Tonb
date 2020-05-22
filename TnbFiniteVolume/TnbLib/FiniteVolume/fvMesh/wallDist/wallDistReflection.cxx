#include <wallDistReflection.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::wallDistReflection::wallDistReflection
(
	const tnbLib::fvMesh& mesh,
	const bool correctWalls
)
	:
	reflectionVectors(mesh),
	wallDistData<wallPointData<vector> >
	(
		mesh,
		reflectionVectors::n_,
		correctWalls
		)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Correct for mesh geom/topo changes
void tnbLib::wallDistReflection::correct()
{
	reflectionVectors::correct();
	wallDistData<wallPointData<vector> >::correct();
}


// ************************************************************************* //