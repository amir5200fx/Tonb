#include <coupledFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(coupledFvPatch, 0);


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	coupledFvPatch::~coupledFvPatch()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void coupledFvPatch::makeCorrVecs(vectorField& cv) const
	{
		// Calculate correction vectors on coupled patches
		const scalarField& patchDeltaCoeffs = deltaCoeffs();

		vectorField patchDeltas = delta();
		vectorField n = nf();

		// If non-orthogonality is over 90 deg, kill correction vector
		// HJ, 27/Feb/2011
		cv = pos(n & patchDeltas)*(n - patchDeltas * patchDeltaCoeffs);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //