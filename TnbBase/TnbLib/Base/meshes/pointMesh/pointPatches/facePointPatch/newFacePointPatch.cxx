#include <facePointPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	autoPtr<facePointPatch> facePointPatch::New
	(
		const polyPatch& patch,
		const pointBoundaryMesh& bm
	)
	{
		if (debug)
		{
			Info << "facePointPatch::New(const polyPatch&, "
				<< " const pointBoundaryMesh&) : "
				<< "constructing facePointPatch"
				<< endl;
		}

		polyPatchConstructorTable::iterator cstrIter =
			polyPatchConstructorTablePtr_->find(patch.type());

		if (cstrIter == polyPatchConstructorTablePtr_->end())
		{
			FatalErrorIn
			(
				"facePointPatch::New(const polyPatch&, "
				"const pointBoundaryMesh&) : "
			) << "Unknown facePointPatch type "
				<< patch.type()
				<< endl << endl
				<< "Valid facePointPatch types are :" << endl
				<< polyPatchConstructorTablePtr_->sortedToc()
				<< exit(FatalError);
		}

		return autoPtr<facePointPatch>(cstrIter()(patch, bm));
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //