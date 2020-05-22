#include <reflectionVectors.hxx>

#include <surfaceFields.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::reflectionVectors::reflectionVectors(const tnbLib::fvMesh& mesh)
	:
	n_
	(
		IOobject
		(
			"reflectionVectors",
			mesh.time().timeName(),
			mesh
		),
		mesh,
		dimensionedVector("n", dimless, vector::zero)
	)
{
	correct();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::reflectionVectors::correct()
{
	const fvMesh& mesh = n_.mesh();
	const fvPatchList& patches = mesh.boundary();

	forAll(patches, patchi)
	{
		// find the nearest face for every cell
		if (patches[patchi].isWall())
		{
			n_.boundaryField()[patchi] =
				mesh.Sf().boundaryField()[patchi]
				/ mesh.magSf().boundaryField()[patchi];
		}
	}
}


// ************************************************************************* //