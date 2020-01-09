#include <pointBoundaryMesh.hxx>

#include <polyBoundaryMesh.hxx>
#include <facePointPatch.hxx>
#include <globalPointPatch.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pointBoundaryMesh::pointBoundaryMesh
(
	const pointMesh& m,
	const polyBoundaryMesh& basicBdry
)
	:
	pointPatchList(basicBdry.size()),
	mesh_(m)
{
	// Set boundary patches
	pointPatchList& Patches = *this;

	forAll(Patches, patchI)
	{
		Patches.set
		(
			patchI,
			facePointPatch::New(basicBdry[patchI], *this).ptr()
		);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pointBoundaryMesh::calcGeometry()
{
	forAll(*this, patchi)
	{
		operator[](patchi).initGeometry();
	}

	forAll(*this, patchi)
	{
		operator[](patchi).calcGeometry();
	}
}


const tnbLib::globalPointPatch&
tnbLib::pointBoundaryMesh::globalPatch() const
{
	const pointPatchList& patches = *this;

	forAll(patches, patchI)
	{
		if (isType<globalPointPatch>(patches[patchI]))
		{
			return refCast<const globalPointPatch>(patches[patchI]);
		}
	}

	FatalErrorIn
	(
		"const pointBoundaryMesh::"
		"globalPointPatch& globalPatch() const"
	) << "patch not found."
		<< abort(FatalError);

	// Dummy return
	return refCast<const globalPointPatch>(patches[0]);
}


void tnbLib::pointBoundaryMesh::movePoints()
{
	pointPatchList& patches = *this;

	forAll(patches, patchi)
	{
		patches[patchi].movePoints();
	}
}


void tnbLib::pointBoundaryMesh::updateMesh()
{
	pointPatchList& patches = *this;

	forAll(patches, patchi)
	{
		patches[patchi].initUpdateMesh();
	}

	forAll(patches, patchi)
	{
		patches[patchi].updateMesh();
	}
}


// ************************************************************************* //