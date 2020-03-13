#include <symmetryFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(symmetryFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, symmetryFvPatch, polyPatch);

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void symmetryFvPatch::makeCorrVecs(vectorField& cv) const
	{
		// Non-orthogonal correction not allowed.  HJ, 16/Apr/2009
		cv = vector::zero;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //