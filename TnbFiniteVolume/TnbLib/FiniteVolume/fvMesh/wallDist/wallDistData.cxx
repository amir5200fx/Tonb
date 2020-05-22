#include <wallDistData.hxx>

#include <patchDataWave.hxx>
#include <wallPolyPatch.hxx>
#include <emptyFvPatchFields.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
template<class TransferType>
tnbLib::wallDistData<TransferType>::wallDistData
(
	const tnbLib::fvMesh& mesh,
	GeometricField<Type, fvPatchField, volMesh>& field,
	const bool correctWalls
)
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
	field_(field),
	correctWalls_(correctWalls),
	nUnset_(0)
{
	correct();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class TransferType>
tnbLib::wallDistData<TransferType>::~wallDistData()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Correct for mesh geom/topo changes
template<class TransferType>
void tnbLib::wallDistData<TransferType>::correct()
{
	Info << "wallDistData.correct() called" << endl;

	const polyMesh& mesh = cellDistFuncs::mesh();

	//
	// Fill data on wall patches with initial values
	//

	const polyBoundaryMesh& bMesh = mesh.boundaryMesh();
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

	// Collect pointers to data on patches
	UPtrList<Field<Type> > patchData(mesh.boundaryMesh().size());

	forAll(field_.boundaryField(), patchI)
	{
		patchData.set(patchI, &field_.boundaryField()[patchI]);
	}

	// Do mesh wave
	patchDataWave<TransferType> wave
	(
		mesh,
		wallPatchIDs,
		patchData,
		correctWalls_
	);

	// Transfer cell values from wave into *this and field_
	transfer(wave.distance());

	field_.transfer(wave.cellData());

	// Transfer values on patches into boundaryField of *this and field_
	forAll(boundaryField(), patchI)
	{
		scalarField& waveFld = wave.patchDistance()[patchI];

		if (!isA<emptyFvPatchScalarField>(boundaryField()[patchI]))
		{
			boundaryField()[patchI].transfer(waveFld);

			Field<Type>& wavePatchData = wave.patchData()[patchI];

			field_.boundaryField()[patchI].transfer(wavePatchData);
		}
	}

	// Transfer number of unset values
	nUnset_ = wave.nUnset();
}


// ************************************************************************* //