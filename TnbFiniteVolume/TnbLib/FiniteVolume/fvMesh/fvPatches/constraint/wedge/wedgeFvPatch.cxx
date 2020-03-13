#include <wedgeFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(wedgeFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, wedgeFvPatch, polyPatch);


	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void wedgeFvPatch::makeCorrVecs(vectorField& cv) const
	{
		// Non-orthogonal correction not allowed.  HJ, 16/Apr/2009
		cv = vector::zero;
	}


	// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

	//- Construct from polyPatch
	wedgeFvPatch::wedgeFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
		:
		fvPatch(patch, bm),
		wedgePolyPatch_(refCast<const wedgePolyPatch>(patch))
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //