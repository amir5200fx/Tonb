#include <fvPatch.hxx>

#include <HashTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::fvPatch> tnbLib::fvPatch::New
(
	const polyPatch& patch,
	const fvBoundaryMesh& bm
)
{
	if (debug)
	{
		Info << "fvPatch::New(const polyPatch&, const fvBoundaryMesh&) : "
			<< "constructing fvPatch"
			<< endl;
	}

	polyPatchConstructorTable::iterator cstrIter =
		polyPatchConstructorTablePtr_->find(patch.type());

	if (cstrIter == polyPatchConstructorTablePtr_->end())
	{
		FatalErrorIn("fvPatch::New(const polyPatch&, const fvBoundaryMesh&)")
			<< "Unknown fvPatch type " << patch.type() << ".\n"
			<< "Valid fvPatch types are :"
			<< polyPatchConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<fvPatch>(cstrIter()(patch, bm));
}


// ************************************************************************* //