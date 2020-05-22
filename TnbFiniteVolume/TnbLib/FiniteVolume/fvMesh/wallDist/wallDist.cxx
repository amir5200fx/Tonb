#include <wallDist.hxx>

#include <patchWave.hxx>
#include <fvMesh.hxx>
#include <wallPolyPatch.hxx>
#include <fvPatchField.hxx>
#include <Field.hxx>
#include <emptyFvPatchFields.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallDist::wallDist(const fvMesh& mesh, const bool correctWalls)
	:
	volScalarField
	(
		IOobject
		(
			"y",
			mesh.time().timeName(),
			mesh
		),
		mesh,
		dimensionedScalar("y", dimLength, GREAT)
	),
	cellDistFuncs(mesh),
	correctWalls_(correctWalls),
	nUnset_(0)
{
	wallDist::correct();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::wallDist::~wallDist()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Correct for mesh geom/topo changes. Might be more intelligent in the
// future (if only small topology change)
void tnbLib::wallDist::correct()
{
	// AJ: make sure to pick up all patches that are specified as a wall
	const polyBoundaryMesh& bMesh = cellDistFuncs::mesh().boundaryMesh();
	labelHashSet wallPatchIDs(bMesh.size());

	forAll(bMesh, patchI)
	{
		if (bMesh[patchI].isWall())
		{
			wallPatchIDs.insert(patchI);
		}
	}

	// Get patchids of walls
	// labelHashSet wallPatchIDs(getPatchIDs<wallPolyPatch>());

	// Calculate distance starting from wallPatch faces.
	patchWave wave(cellDistFuncs::mesh(), wallPatchIDs, correctWalls_);

	// Transfer cell values from wave into *this
	transfer(wave.distance());

	// Transfer values on patches into boundaryField of *this
	forAll(boundaryField(), patchI)
	{
		if (!isA<emptyFvPatchScalarField>(boundaryField()[patchI]))
		{
			scalarField& waveFld = wave.patchDistance()[patchI];

			boundaryField()[patchI].transfer(waveFld);
		}
	}

	// Transfer number of unset values
	nUnset_ = wave.nUnset();
}


// ************************************************************************* //