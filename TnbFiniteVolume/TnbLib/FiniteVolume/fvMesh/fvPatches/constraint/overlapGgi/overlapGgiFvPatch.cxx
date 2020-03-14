#include <overlapGgiFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvBoundaryMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(overlapGgiFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, overlapGgiFvPatch, polyPatch);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

// Make patch weighting factors
void tnbLib::overlapGgiFvPatch::makeWeights(scalarField& w) const
{
	// Calculation of weighting factors is performed from the master
	// position, using reconstructed shadow cell centres
	// HJ, 2/Aug/2007
	if (overlapGgiPolyPatch_.master())
	{
		vectorField n = nf();

		// Note: mag in the dot-product.
		// For all valid meshes, the non-orthogonality will be less than
		// 90 deg and the dot-product will be positive.  For invalid
		// meshes (d & s <= 0), this will stabilise the calculation
		// but the result will be poor.  HJ, 24/Aug/2011
		scalarField nfc =
			mag(n & (overlapGgiPolyPatch_.reconFaceCellCentres() - Cf()));

		w = nfc / (mag(n & (Cf() - Cn())) + nfc);
	}
	else
	{
		// Pick up weights from the master side
		scalarField masterWeights(shadow().size());
		shadow().makeWeights(masterWeights);

		w = interpolate(1 - masterWeights);
	}
}


// Make patch face - neighbour cell distances
void tnbLib::overlapGgiFvPatch::makeDeltaCoeffs(scalarField& dc) const
{
	if (overlapGgiPolyPatch_.master())
	{
		// Stabilised form for bad meshes.  HJ, 24/Aug/2011
		vectorField d = delta();

		dc = 1.0 / max(nf() & d, 0.05*mag(d));
	}
	else
	{
		scalarField masterDeltas(shadow().size());
		shadow().makeDeltaCoeffs(masterDeltas);
		dc = interpolate(masterDeltas);
	}
}


void tnbLib::overlapGgiFvPatch::makeCorrVecs(vectorField& cv) const
{
	// Non-orthogonality correction on a ggi interface
	// MB, 7/April/2009

	// Calculate correction vectors on coupled patches
	const scalarField& patchDeltaCoeffs = deltaCoeffs();

	vectorField patchDeltas = delta();
	vectorField n = nf();
	cv = n - patchDeltas * patchDeltaCoeffs;
}


const tnbLib::overlapGgiFvPatch& tnbLib::overlapGgiFvPatch::shadow() const
{
	const fvPatch& p =
		this->boundaryMesh()[overlapGgiPolyPatch_.shadowIndex()];

	return refCast<const overlapGgiFvPatch>(p);
}


// Return delta (P to N) vectors across coupled patch
tnbLib::tmp<tnbLib::vectorField> tnbLib::overlapGgiFvPatch::delta() const
{
	if (overlapGgiPolyPatch_.master())
	{
		return overlapGgiPolyPatch_.reconFaceCellCentres() - Cn();
	}
	else
	{
		//         vectorField masterDelta = shadow().Cn()
		//             - overlapGgiPolyPatch_.shadow().reconFaceCellCentres();

		//         return interpolate(masterDelta);

		return interpolate
		(
			shadow().Cn()
			- overlapGgiPolyPatch_.shadow().reconFaceCellCentres()
		);
	}
}


tnbLib::tmp<tnbLib::labelField> tnbLib::overlapGgiFvPatch::interfaceInternalField
(
	const unallocLabelList& internalData
) const
{
	return patchInternalField(internalData);
}


tnbLib::tmp<tnbLib::labelField> tnbLib::overlapGgiFvPatch::transfer
(
	const Pstream::commsTypes,
	const unallocLabelList& interfaceData
) const
{
	notImplemented
	(
		"overlapGgiFvPatchField<Type>::"
		"transfer(const unallocLabelList& interfaceData) const"
	);

	return labelField::null();
}


tnbLib::tmp<tnbLib::labelField> tnbLib::overlapGgiFvPatch::internalFieldTransfer
(
	const Pstream::commsTypes,
	const unallocLabelList& iF
) const
{
	return shadow().patchInternalField(iF);
}


// ************************************************************************* //