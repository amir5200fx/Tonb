#include <nearWallDist.hxx>

#include <tnbTime.hxx>
#include <fvMesh.hxx>
#include <cellDistFuncs.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::nearWallDist::doAll()
{
	cellDistFuncs wallUtils(mesh_);

	// AJ: make sure to pick up all patches that are specified as a wall
	const polyBoundaryMesh& bMesh = wallUtils.mesh().boundaryMesh();
	labelHashSet wallPatchIDs(bMesh.size());
	forAll(bMesh, patchI)
	{
		if (bMesh[patchI].isWall())
		{
			wallPatchIDs.insert(patchI);
		}
	}

	// Get patch ids of walls
	// labelHashSet wallPatchIDs(wallUtils.getPatchIDs<wallPolyPatch>());

	// Size neighbours array for maximum possible

	labelList neighbours(wallUtils.maxPatchSize(wallPatchIDs));


	// Correct all cells with face on wall

	const volVectorField& cellCentres = mesh_.C();

	forAll(mesh_.boundary(), patchI)
	{
		fvPatchScalarField& ypatch = operator[](patchI);

		const fvPatch& patch = mesh_.boundary()[patchI];

		if (patch.isWall())
		{
			const polyPatch& pPatch = patch.patch();

			const unallocLabelList& faceCells = patch.faceCells();

			// Check cells with face on wall
			forAll(patch, patchFaceI)
			{
				label nNeighbours = wallUtils.getPointNeighbours
				(
					pPatch,
					patchFaceI,
					neighbours
				);

				label minFaceI = -1;

				ypatch[patchFaceI] = wallUtils.smallestDist
				(
					cellCentres[faceCells[patchFaceI]],
					pPatch,
					nNeighbours,
					neighbours,
					minFaceI
				);
			}
		}
		else
		{
			ypatch = 0.0;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::nearWallDist::nearWallDist(const tnbLib::fvMesh& mesh)
	:
	volScalarField::GeometricBoundaryField
	(
		mesh.boundary(),
		mesh.V(),           // Dummy internal field,
		calculatedFvPatchScalarField::typeName
	),
	mesh_(mesh)
{
	doAll();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::nearWallDist::~nearWallDist()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::nearWallDist::correct()
{
	if (mesh_.changing())
	{
		// Update size of GeometricBoundaryField
		forAll(mesh_.boundary(), patchI)
		{
			operator[](patchI).setSize(mesh_.boundary()[patchI].size());
		}
	}

	doAll();
}


// ************************************************************************* //