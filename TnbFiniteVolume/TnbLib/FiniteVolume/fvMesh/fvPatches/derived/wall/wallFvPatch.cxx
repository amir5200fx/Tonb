#include <wallFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(wallFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, wallFvPatch, polyPatch);


	// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

	void wallFvPatch::makeCorrVecs(vectorField& cv) const
	{
		cv = vector::zero;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //